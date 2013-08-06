#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContext.hpp>

#include <yandex/contest/invoker/Process.hpp>

#include <bunsan/forward_constructor.hpp>

#include <boost/noncopyable.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat
{
    class ProcessContext: public detail::BasicContext<ProcessPointer, std::shared_ptr<void>>
    {
    private:
        friend class ProcessGroupContext;

        BUNSAN_FORWARD_EXPLICIT_CONSTRUCTOR(ProcessContext, Context)
    };
}}}}
