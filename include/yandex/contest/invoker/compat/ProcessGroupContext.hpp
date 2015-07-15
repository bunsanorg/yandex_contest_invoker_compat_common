#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContext.hpp>
#include <yandex/contest/invoker/compat/detail/Handle.hpp>
#include <yandex/contest/invoker/compat/ProcessContext.hpp>

#include <yandex/contest/invoker/ProcessGroup.hpp>

#include <bunsan/forward_constructor.hpp>

#include <boost/noncopyable.hpp>

#include <memory>
#include <utility>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {

class ProcessGroupContext
    : public detail::BasicContext<ProcessGroupPointer, ProcessContext>,
      public std::enable_shared_from_this<ProcessGroupContext> {
 public:
  using Handle = detail::Handle<ProcessGroupContext>;

 public:
  template <typename... Args>
  Handle createProcess(Args &&... args) {
    return Handle(shared_from_this(),
                  registerChildContext(ProcessContext::make_shared(
                      member().createProcess(std::forward<Args>(args)...))));
  }

 private:
  friend class ContainerContext;

  template <typename... Args>
  static std::shared_ptr<ProcessGroupContext> make_shared(Args &&... args) {
    std::shared_ptr<ProcessGroupContext> ctx(
        new ProcessGroupContext(std::forward<Args>(args)...));
    return ctx;
  }

  BUNSAN_FORWARD_EXPLICIT_CONSTRUCTOR(ProcessGroupContext, Context)
};

using ProcessHandle = ProcessGroupContext::Handle;

}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
