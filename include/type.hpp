// 
// Copyright 2022 Clemens Cords
// Created on 07.02.22 by clem (mail@clemens-cords.com)
//

#pragma once

#include <include/julia_wrapper.hpp>
#include <include/typedefs.hpp>
#include <include/proxy.hpp>
#include <include/symbol.hpp>

namespace jluna
{
    /// @brief forward declaration
    class Type : public Proxy
    {
        public:
            /// @brief default ctor, construct as Nothing
            Type();

            /// @brief construct from C++ type
            /// @param to_julia_type meta template
            template<ToJuliaTypeConvertable T>
            static Type construct_from();

            /// @brief ctor
            /// @param value
            Type(jl_datatype_t* value);

            /// @brief ctor
            /// @param proxy
            Type(Proxy*);

            /// @brief decay to C-type
            operator jl_datatype_t*();

            /// @brief unroll type as much as possible
            Type unroll() const;

            /// @brief get direct super type
            Type get_super_type() const;

            /// @brief get name
            Symbol get_symbol() const;

            /// @brief get number of parameters
            /// @returns size_t
            size_t get_n_parameters() const;

            /// @brief get parameter names
            /// @returns vector
            std::vector<std::pair<Symbol, Type>> get_parameters() const;

            /// @brief get number of fields
            /// @returns size_t
            size_t get_n_fields() const;

            /// @brief get field names
            /// @returns vector
            std::vector<std::pair<Symbol, Type>> get_fields() const;

            /// @brief if type is singleton, get instance of that singleton
            /// @returns instance ptr if singleton-type, nullptr otherwise
            unsafe::Value* get_singleton_instance() const;

            /// @brief this <: other
            /// @param other
            /// @returns true if subtype, false otherwise
            bool is_subtype_of(const Type&) const;

            /// @brief this <: other
            /// @param other
            /// @returns true if subtype, false otherwise
            bool operator<(const Type&) const;

            /// @brief other <: this
            /// @param other
            /// @returns true if super, false otherwise
            bool is_supertype_of(const Type&) const;

            /// @brief this <: other
            /// @param other
            /// @returns true if subtype, false otherwise
            bool operator>(const Type&) const;

            /// @brief this === other
            /// @param other
            /// @returns true if both are the same type, false otherwise
            bool is_same_as(const Type&) const;

            /// @brief this === other
            /// @param other
            /// @returns true if both are the same type, false otherwise
            bool operator==(const Type&) const;

            /// @brief not(this === other)
            /// @param other
            /// @returns true if both are the same type, false otherwise
            bool operator!=(const Type&) const;

            /// @brief is primitive type
            /// @returns bool
            bool is_primitive() const;

            /// @brief is struct type
            /// @returns bool
            bool is_struct_type() const;

            /// @brief is mutable
            /// @returns bool
            bool is_declared_mutable() const;

            /// @brief is bits type
            /// @returns bool
            bool is_isbits() const;

            /// @brief is singleton
            /// @returns bool
            bool is_singleton() const;

            /// @brief is abstract
            /// @returns bool
            bool is_abstract_type() const;

            /// @brief is abstract ref
            /// @returns bool
            bool is_abstract_ref_type() const;

            /// @brief check if .name property of unrolled type is equal to typename
            /// @param symbol: name of type, evaluated to Main.eval(symbol)
            /// @returns bool
            bool is_typename(const std::string& symbol);

            /// @brief check if .name property of unrolled type is equal to typename
            /// @param type
            /// @returns bool
            bool is_typename(const Type& other);

        private:
            jl_datatype_t* get() const;
    };

    inline Type AbstractArray_t;
    inline Type AbstractChar_t;
    inline Type AbstractFloat_t;
    inline Type AbstractString_t;
    inline Type Any_t;
    inline Type Array_t;
    inline Type Bool_t;
    inline Type Char_t;
    inline Type DataType_t;
    inline Type DenseArray_t;
    inline Type Exception_t;
    inline Type Expr_t;
    inline Type Float16_t;
    inline Type Float32_t;
    inline Type Float64_t;
    inline Type Function_t;
    inline Type GlobalRef_t;
    inline Type IO_t;
    inline Type Int128_t;
    inline Type Int16_t;
    inline Type Int32_t;
    inline Type Int64_t;
    inline Type Int8_t;
    inline Type Integer_t;
    inline Type LineNumberNode_t;
    inline Type Method_t;
    inline Type Module_t;
    inline Type NTuple_t;
    inline Type NamedTuple_t;
    inline Type Nothing_t;
    inline Type Number_t;
    inline Type Pair_t;
    inline Type Ptr_t;
    inline Type QuoteNode_t;
    inline Type Real_t;
    inline Type Ref_t;
    inline Type Signed_t;
    inline Type String_t;
    inline Type Symbol_t;
    inline Type Task_t;
    inline Type Tuple_t;
    inline Type Type_t;
    inline Type TypeVar_t;
    inline Type UInt128_t;
    inline Type UInt16_t;
    inline Type UInt32_t;
    inline Type UInt64_t;
    inline Type UInt8_t;
    inline Type UndefInitializer_t;
    inline Type Union_t;
    inline Type UnionAll_t;
    inline Type UnionEmpty_t;
    inline Type Unsigned_t;
    inline Type VecElement_t;
    inline Type WeakRef_t;
    
    namespace unsafe
    {
        static inline unsafe::Value* AbstractArray_t;
        static inline unsafe::Value* AbstractChar_t;
        static inline unsafe::Value* AbstractFloat_t;
        static inline unsafe::Value* AbstractString_t;
        static inline unsafe::Value* Any_t;
        static inline unsafe::Value* Array_t;
        static inline unsafe::Value* Bool_t;
        static inline unsafe::Value* Char_t;
        static inline unsafe::Value* DataType_t;
        static inline unsafe::Value* DenseArray_t;
        static inline unsafe::Value* Exception_t;
        static inline unsafe::Value* Expr_t;
        static inline unsafe::Value* Float16_t;
        static inline unsafe::Value* Float32_t;
        static inline unsafe::Value* Float64_t;
        static inline unsafe::Value* Function_t;
        static inline unsafe::Value* GlobalRef_t;
        static inline unsafe::Value* IO_t;
        static inline unsafe::Value* Int128_t;
        static inline unsafe::Value* Int16_t;
        static inline unsafe::Value* Int32_t;
        static inline unsafe::Value* Int64_t;
        static inline unsafe::Value* Int8_t;
        static inline unsafe::Value* Integer_t;
        static inline unsafe::Value* LineNumberNode_t;
        static inline unsafe::Value* Method_t;
        static inline unsafe::Value* Module_t;
        static inline unsafe::Value* NTuple_t;
        static inline unsafe::Value* NamedTuple_t;
        static inline unsafe::Value* Nothing_t;
        static inline unsafe::Value* Number_t;
        static inline unsafe::Value* Pair_t;
        static inline unsafe::Value* Ptr_t;
        static inline unsafe::Value* QuoteNode_t;
        static inline unsafe::Value* Real_t;
        static inline unsafe::Value* Ref_t;
        static inline unsafe::Value* Signed_t;
        static inline unsafe::Value* String_t;
        static inline unsafe::Value* Symbol_t;
        static inline unsafe::Value* Task_t;
        static inline unsafe::Value* Tuple_t;
        static inline unsafe::Value* Type_t;
        static inline unsafe::Value* TypeVar_t;
        static inline unsafe::Value* UInt128_t;
        static inline unsafe::Value* UInt16_t;
        static inline unsafe::Value* UInt32_t;
        static inline unsafe::Value* UInt64_t;
        static inline unsafe::Value* UInt8_t;
        static inline unsafe::Value* UndefInitializer_t;
        static inline unsafe::Value* Union_t;
        static inline unsafe::Value* UnionAll_t;
        static inline unsafe::Value* UnionEmpty_t;
        static inline unsafe::Value* Unsigned_t;
        static inline unsafe::Value* VecElement_t;
        static inline unsafe::Value* WeakRef_t;
    }
}

#include <.src/type.inl>