#pragma once

#include <cuj/dsl/class.h>
#include <cuj/dsl/pointer.h>

CUJ_NAMESPACE_BEGIN(cuj::dsl)

namespace class_detail
{

    template<typename C, typename M>
    Pointer<M> class_pointer_to_member_ptr(
        const Pointer<C> &class_ptr, size_t member_index)
    {
        auto func_ctx = FunctionContext::get_func_context();
        auto type_ctx = func_ctx->get_type_context();
        
        auto class_ptr_type = type_ctx->get_type<Pointer<C>>();
        auto member_ptr_type = type_ctx->get_type<Pointer<M>>();
        
        core::ClassPointerToMemberPointer class_to_member = {
            .class_ptr_type  = class_ptr_type,
            .member_ptr_type = member_ptr_type,
            .class_ptr       = newRC<core::Expr>(class_ptr._load()),
            .member_index    = member_index
        };
        return Pointer<M>::_from_expr(std::move(class_to_member));
    }

    template<typename C>
    Pointer<C> alloc_local_var()
    {
        auto func_ctx = FunctionContext::get_func_context();
        auto type_ctx = func_ctx->get_type_context();
        auto type = type_ctx->get_type<C>();
        core::LocalAllocAddr addr = {
            .alloc_type  = type,
            .alloc_index = func_ctx->alloc_local_var(type)
        };
        return Pointer<C>::_from_expr(std::move(addr));
    }

} // namespace class_detail

CUJ_NAMESPACE_END(cuj::dsl)
