cmake_minimum_required(VERSION 3.12)

#[=======================================================================[.rst:

Build jluna
-----------

This cmake attempts to automatically detect the Julia image.
If this is not possible, manually specify the path to the Julia binary using:

    ``-DJULIA_BINDIR=/path/to/.../julia/bin``

If you are unsure of the location of this folder, you can access
it from within the REPL using:

    ``println(Sys.BINDIR)``

Options
^^^^^^^
``jluna_DEVELOPER_MODE``
    enable building test and benchmark executables. Off by default
``BUILD_TESTING``
    build jluna_test, as CTest. On by default
``BUILD_BENCHMARK``
    build jluna_benchmark. Off by default

#]=======================================================================]

project(jluna VERSION 0.9.1 LANGUAGES CXX)

### Find Julia ###

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/find")
find_package(Julia 1.7.0 REQUIRED)

### Find Threads ###

find_package(Threads)

### Configure Files ###

file(READ
    include/julia/jluna.jl
    JLUNA_JULIA_SOURCE
)

configure_file("${CMAKE_SOURCE_DIR}/.src/include_julia.inl.in" "${CMAKE_SOURCE_DIR}/.src/include_julia.inl" @ONLY)

### Declare Library ###

add_library(jluna SHARED
    jluna.hpp

    include/exceptions.hpp
    .src/exceptions.cpp

    include/typedefs.hpp
    .src/typedefs.inl

    include/unsafe_utilities.hpp
    .src/unsafe_utilities.inl
    .src/unsafe_utilities.cpp

    include/safe_utilities.hpp
    .src/safe_utilities.inl
    .src/safe_utilities.cpp

    include/concepts.hpp

    include/box.hpp
    .src/box.inl

    include/unbox.hpp
    .src/unbox.inl

    include/proxy.hpp
    .src/proxy.cpp
    .src/proxy.inl

    include/array.hpp
    .src/array.inl
    .src/array_iterator.inl

    include/cppcall.hpp
    .src/cppcall.inl

    include/module.hpp
    .src/module.cpp
    .src/module.inl

    include/symbol.hpp
    .src/symbol.cpp
    .src/symbol.inl

    include/type.hpp
    .src/type.cpp
    .src/type.inl

    include/generator_expression.hpp
    .src/generator_expression.cpp

    include/usertype.hpp
    .src/usertype.inl

    include/multi_threading.hpp
    .src/multi_threading.inl

    include/mutex.hpp
    .src/mutex.cpp

    .src/c_adapter.hpp
    .src/c_adapter.cpp
)

target_compile_features(jluna PUBLIC cxx_std_20)
target_include_directories(
  jluna 
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/jluna>"
  )
target_link_libraries(jluna PUBLIC
    "Julia::Julia"
    "Threads::Threads"
)

### HACK: export all symbols on Windows ###
set_target_properties(jluna PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS YES # TODO
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION}"
)

### Install rules ###
include(GNUInstallDirs)
install(TARGETS jluna EXPORT JlunaTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
install(EXPORT JlunaTargets NAMESPACE Jluna:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jluna/)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/JlunaConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/JlunaConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jluna
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/JlunaConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/find/FindJulia.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/JlunaConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/JlunaConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jluna
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jluna/include)

include(CTest)
### Declare Test ###

option(BUILD_TESTING "Enable jluna_test" ON)
if (BUILD_TESTING)
    add_executable(
        jluna_test
        .test/main.cpp
        .test/test.hpp
    )
    target_link_libraries(jluna_test PRIVATE jluna)
    add_test(NAME jluna_test COMMAND jluna_test)
endif()

### Developer mode ###

if(NOT jluna_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
        AUTHOR_WARNING
        "Developer mode is intended for developers of jluna"
    )
endif()

### Declare Benchmark ###

option(BUILD_BENCHMARK "Enable jluna_benchmark" OFF)
if (BUILD_BENCHMARK) # AND NOT WIN32)
    add_executable(
        jluna_benchmark
        .benchmark/main.cpp
        .benchmark/benchmark.hpp
        .benchmark/benchmark_aux.hpp
    )
    target_link_libraries(jluna_benchmark PRIVATE jluna)
endif()
