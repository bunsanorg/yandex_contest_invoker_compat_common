#pragma once

#include "yandex/contest/invoker/compat/detail/BasicContextHandle.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace detail
{
    template <typename Context_>
    class Handle: public BasicContextHandle<Context_>
    {
    public:
        typedef BasicContextHandle<Context_> Parent;

    public:
        using Parent::context;
        using Parent::member;

        template <typename ... Args>
        explicit Handle(Args &&...args):
            Parent(std::forward<Args>(args)...) {}
    };
}}}}}
