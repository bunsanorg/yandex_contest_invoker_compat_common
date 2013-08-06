#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContext.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace detail
{
    struct InvalidHandleError: virtual Error {};

    template <typename Context_>
    class BasicContextHandle
    {
    public:
        typedef BasicContextHandle<Context_> ContextHandle;
        typedef Context_ Context;
        typedef typename Context::ChildContext ChildContext;
        typedef typename ChildContext::Member Member;
        typedef std::shared_ptr<Context> ContextSharedPtr;
        typedef std::weak_ptr<Context> ContextWeakPtr;

    public:
        BasicContextHandle(const ContextHandle &)=default;
        BasicContextHandle &operator=(const ContextHandle &)=default;

        void destroy()
        {
            ContextSharedPtr ctx = context_.lock();
            if (ctx)
                ctx->destroyChild(id_);
        }

        explicit operator bool() const
        {
            return !context_.expired();
        }

    protected:
        BasicContextHandle()=default;

        BasicContextHandle(const ContextWeakPtr &context, const Id id):
            context_(context), id_(id) {}

        ChildContext &context()
        {
            ContextSharedPtr ctx = context_.lock();
            if (!ctx)
                BOOST_THROW_EXCEPTION(InvalidHandleError());
            return ctx->child(id_);
        }

        Member &member()
        {
            return context().member();
        }

    private:
        ContextWeakPtr context_;
        Id id_ = 0;
    };
}}}}}
