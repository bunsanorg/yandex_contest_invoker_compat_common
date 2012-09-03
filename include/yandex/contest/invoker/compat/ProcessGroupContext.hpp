#pragma once

#include "yandex/contest/invoker/ProcessGroup.hpp"

#include "yandex/contest/invoker/compat/ProcessContext.hpp"

#include "yandex/contest/invoker/compat/detail/BasicContext.hpp"
#include "yandex/contest/invoker/compat/detail/Handle.hpp"

#include <memory>

#include <boost/noncopyable.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat
{
    class ProcessGroupContext:
        public detail::BasicContext<ProcessGroupPointer, ProcessContext>,
        public std::enable_shared_from_this<ProcessGroupContext>
    {
    public:
        typedef detail::Handle<ProcessGroupContext> Handle;

    public:
        template <typename ... Args>
        Handle createProcess(Args &&...args)
        {
            std::shared_ptr<ProcessContext> ctx(
                new ProcessContext(
                    member().createProcess(std::forward<Args>(args)...)));
            return Handle(shared_from_this(), registerChildContext(std::move(ctx)));
        }

    private:
        friend class ContainerContext;

        template <typename ... Args>
        explicit ProcessGroupContext(Args &&...args):
            Context(std::forward<Args>(args)...) {}
    };

    typedef ProcessGroupContext::Handle ProcessHandle;
}}}}
