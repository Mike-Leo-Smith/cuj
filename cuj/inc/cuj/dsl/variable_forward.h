#pragma once

#include <cuj/common.h>

CUJ_NAMESPACE_BEGIN(cuj::dsl)

struct CujVoid { };

// arithmetic

template<typename T> requires std::is_arithmetic_v<T>
class Arithmetic;

template<typename T>
struct IsCujArithmetic : std::false_type { };

template<typename T>
struct IsCujArithmetic<Arithmetic<T>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_arithmetic_v = IsCujArithmetic<T>::value;

// pointer

template<typename T>
class Pointer;

template<typename T>
struct IsCujPointer : std::false_type { };

template<typename T>
struct IsCujPointer<Pointer<T>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_pointer_v = IsCujPointer<T>::value;

// array

template<typename T, size_t N>
class Array;

template<typename T>
struct IsCujArray : std::false_type { };

template<typename T, size_t N>
struct IsCujArray<Array<T, N>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_array_v = IsCujArray<T>::value;

// class

template<typename T>
concept CujClass = requires
{
    typename T::CujClassTag;
};

template<typename T>
constexpr bool is_cuj_class_v = CujClass<T>;

template<typename T>
constexpr bool is_cuj_var_v =
    is_cuj_arithmetic_v<T>     ||
    is_cuj_pointer_v<T>        ||
    std::is_same_v<T, CujVoid> ||
    is_cuj_array_v<T>          ||
    is_cuj_class_v<T>;

// reference

template<typename T>
class ref { };

template<typename T>
struct IsCujReferenceWrapper : std::false_type { };

template<typename T>
struct IsCujReferenceWrapper<ref<T>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_reference_wrapper_v = IsCujReferenceWrapper<T>::value;

template<typename T>
struct IsCujArithmeticReference : std::false_type { };

template<typename T>
struct IsCujArithmeticReference<ref<Arithmetic<T>>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_arithmetic_reference_v = IsCujArithmeticReference<T>::value;

template<typename T>
struct IsCujPointerReference : std::false_type { };

template<typename T>
struct IsCujPointerReference<ref<Pointer<T>>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_pointer_reference_v = IsCujPointerReference<T>::value;

template<typename T>
struct IsCujArrayReference : std::false_type { };

template<typename T, size_t N>
struct IsCujArrayReference<ref<Array<T, N>>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_array_reference_v = IsCujArrayReference<T>::value;

template<typename T>
struct IsCujClassReference : std::false_type { };

template<typename T> requires is_cuj_class_v<T>
struct IsCujClassReference<ref<T>> : std::true_type { };

template<typename T>
constexpr bool is_cuj_class_reference_v = IsCujClassReference<T>::value;

template<typename T>
constexpr bool is_cuj_ref_v =
    is_cuj_reference_wrapper_v<T>    ||
    is_cuj_arithmetic_reference_v<T> ||
    is_cuj_pointer_reference_v<T>    ||
    is_cuj_array_reference_v<T>      ||
    is_cuj_class_reference_v<T>;

// conv

template<typename T>
struct RemoveReference { using Type = T; };

template<typename T>
struct RemoveReference<ref<T>> { using Type = T; };

template<typename T>
using add_reference_t = ref<T>;

template<typename T>
using remove_reference_t = typename RemoveReference<T>::Type;

// c++ to cuj

template<typename T>
struct CXXToCuj { using Type = void; };

template<typename T> requires std::is_arithmetic_v<T>
struct CXXToCuj<T> { using Type = Arithmetic<T>; };

template<>
struct CXXToCuj<void> { using Type = CujVoid; };

template<typename T>
struct CXXToCuj<T *> { using Type = Pointer<typename CXXToCuj<T>::Type>; };

template<typename T, size_t N>
struct CXXToCuj<T[N]> { using Type = Array<typename CXXToCuj<T>::Type, N>; };

template<typename T>
struct CXXClassToCujClass;

template<typename T>
struct CujToCXX { using Type = void; };

template<typename T>
struct CujToCXX<Arithmetic<T>> { using Type = T; };

template<>
struct CujToCXX<CujVoid> { using Type = void; };

template<typename T>
struct CujToCXX<Pointer<T>> { using Type = typename CujToCXX<T>::Type *; };

template<typename T, size_t N>
struct CujToCXX<Array<T, N>> { using Type = typename CujToCXX<T>::Type[N]; };

template<typename T>
struct CujClassToCXXClass;

namespace detail
{

    void *_cxx_class_to_cuj_class(...);

    template<typename CXXClass>
    auto cxx_class_to_cuj_class_aux()
    {
        using LocalRegisteredType = std::remove_pointer_t<
            decltype(_cxx_class_to_cuj_class(std::declval<CXXClass *>()))>;

        if constexpr(!std::is_same_v<LocalRegisteredType, void>)
        {
            return static_cast<LocalRegisteredType *>(nullptr);
        }
        else
        {
            using GlobalRegisteredType =
                typename CXXClassToCujClass<CXXClass>::Type;

            return static_cast<GlobalRegisteredType *>(nullptr);
        }
    }

    template<typename CXXClass>
    using cxx_class_to_cuj_class_t = std::remove_pointer_t<
        decltype(cxx_class_to_cuj_class_aux<CXXClass>())>;

} // namespace detail

template<typename T> requires std::is_class_v<T>
struct CXXToCuj<T> { using Type = detail::cxx_class_to_cuj_class_t<T>; };

template<typename T> requires is_cuj_class_v<T>
struct CujToCXX<T> { using Type = typename T::CXXClass; };

template<typename T>
using cxx_to_cuj_t = typename CXXToCuj<T>::Type;

template<typename T>
using cuj_to_cxx_t = typename CujToCXX<T>::Type;

template<typename T>
using cxx_to_cuj_ref_t = add_reference_t<cxx_to_cuj_t<T>>;

template<typename T>
using ptr = Pointer<T>;

template<typename T>
using num = Arithmetic<T>;

template<typename T, size_t N>
using arr = Array<T, N>;

template<typename T>
using cxx = cxx_to_cuj_t<T>;

CUJ_NAMESPACE_END(cuj::dsl)
