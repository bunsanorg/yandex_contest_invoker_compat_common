#pragma once

#include "yandex/contest/invoker/Container.hpp"

#include "yandex/contest/invoker/compat/ProcessGroupContext.hpp"

#include "yandex/contest/invoker/compat/detail/BasicContext.hpp"
#include "yandex/contest/invoker/compat/detail/Handle.hpp"

#include <memory>

#include <boost/noncopyable.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat
{
    class ContainerContext:
        public detail::BasicContext<ContainerPointer, ProcessGroupContext>,
        public std::enable_shared_from_this<ContainerContext>
    {
    public:
        typedef detail::Handle<ContainerContext> Handle;

    public:
        template <typename ... Args>
        static std::shared_ptr<ContainerContext> create(Args &&...args)
        {
            const std::shared_ptr<ContainerContext> ctx(
                new ContainerContext(Container::create(std::forward<Args>(args)...)));
            return ctx;
        }

        template <typename ... Args>
        Handle createProcessGroup(Args &&...args)
        {
            std::shared_ptr<ProcessGroupContext> ctx(
                new ProcessGroupContext(
                    member().createProcessGroup(std::forward<Args>(args)...)));
            return Handle(shared_from_this(), registerChildContext(std::move(ctx)));
        }

    private:
        template <typename ... Args>
        explicit ContainerContext(Args &&...args):
            Context(std::forward<Args>(args)...) {}
    };

    typedef std::shared_ptr<ContainerContext> ContainerContextPointer;
    typedef ContainerContext::Handle ProcessGroupHandle;
}}}}
