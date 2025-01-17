#pragma once

#include <cuj/dsl/arithmetic.h>
#include <cuj/dsl/arithmetic_reference.h>
#include <cuj/dsl/array.h>
#include <cuj/dsl/array_reference.h>
#include <cuj/dsl/class.h>
#include <cuj/dsl/function.h>
#include <cuj/dsl/if.h>
#include <cuj/dsl/loop.h>
#include <cuj/dsl/module.h>
#include <cuj/dsl/pointer.h>
#include <cuj/dsl/pointer_reference.h>
#include <cuj/dsl/reference.h>
#include <cuj/dsl/return.h>
#include <cuj/dsl/switch.h>
#include <cuj/dsl/type_context.h>
#include <cuj/dsl/variable.h>
#include <cuj/gen/gen.h>

#include <cuj/dsl/impl/arithmetic.inl>
#include <cuj/dsl/impl/arithmetic_reference.inl>
#include <cuj/dsl/impl/array.inl>
#include <cuj/dsl/impl/array_reference.inl>
#include <cuj/dsl/impl/class.inl>
#include <cuj/dsl/impl/function.inl>
#include <cuj/dsl/impl/if.inl>
#include <cuj/dsl/impl/loop.inl>
#include <cuj/dsl/impl/pointer.inl>
#include <cuj/dsl/impl/pointer_reference.inl>
#include <cuj/dsl/impl/return.inl>
#include <cuj/dsl/impl/switch.inl>
#include <cuj/dsl/impl/type_context.inl>

CUJ_NAMESPACE_BEGIN(cuj)

using i8  = dsl::Arithmetic<int8_t>;
using i16 = dsl::Arithmetic<int16_t>;
using i32 = dsl::Arithmetic<int32_t>;
using i64 = dsl::Arithmetic<int64_t>;

using u8  = dsl::Arithmetic<uint8_t>;
using u16 = dsl::Arithmetic<uint16_t>;
using u32 = dsl::Arithmetic<uint32_t>;
using u64 = dsl::Arithmetic<uint64_t>;

using f32 = dsl::Arithmetic<float>;
using f64 = dsl::Arithmetic<double>;

using boolean = dsl::Arithmetic<bool>;
using char_t = dsl::Arithmetic<char>;

using dsl::Function;
using dsl::Module;
using dsl::ScopedModule;

using dsl::var;
using dsl::ref;

using dsl::ptr;
using dsl::num;
using dsl::arr;
using dsl::cxx;

using dsl::function;
using dsl::kernel;
using dsl::declare;

CUJ_NAMESPACE_END(cuj)
