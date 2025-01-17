#pragma once

#include <cuj/core/expr.h>
#include <cuj/dsl/variable_forward.h>

CUJ_NAMESPACE_BEGIN(cuj::dsl)

template<typename T, size_t N>
class Array
{
    size_t alloc_index_;

    static const core::Type *type();

public:

    using ElementType = T;

    static constexpr size_t ElementCount = N;

    Array();

    Array(const ref<Array<T, N>> &ref);

    Array(const Array &other);

    Array(Array &&other) noexcept;

    Array &operator=(const Array &other);

    constexpr size_t size() const { return N; }

    template<typename U> requires std::is_integral_v<U>
    add_reference_t<T> operator[](const Arithmetic<U> &idx) const;

    template<typename U> requires std::is_integral_v<U>
    add_reference_t<T> operator[](U idx) const;

    Pointer<Array> address() const;

    core::ArrayAddrToFirstElemAddr _first_elem_addr() const;
};

CUJ_NAMESPACE_END(cuj::dsl)
