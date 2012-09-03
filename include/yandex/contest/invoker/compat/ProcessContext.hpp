#pragma once

#include "yandex/contest/invoker/Process.hpp"

#include "yandex/contest/invoker/compat/detail/BasicContext.hpp"

#include <boost/noncopyable.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat
{
    class ProcessContext: public detail::BasicContext<ProcessPointer, std::shared_ptr<void>>
    {
    private:
        friend class ProcessGroupContext;

        template <typename ... Args>
        explicit ProcessContext(Args &&...args):
            Context(std::forward<Args>(args)...) {}
    };
}}}}
