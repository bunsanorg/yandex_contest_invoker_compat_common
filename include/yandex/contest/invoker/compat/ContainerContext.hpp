#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContext.hpp>
#include <yandex/contest/invoker/compat/detail/Handle.hpp>
#include <yandex/contest/invoker/compat/ProcessGroupContext.hpp>

#include <yandex/contest/invoker/Container.hpp>

#include <bunsan/forward_constructor.hpp>

#include <boost/noncopyable.hpp>

#include <memory>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {

class ContainerContext
    : public detail::BasicContext<ContainerPointer, ProcessGroupContext>,
      public std::enable_shared_from_this<ContainerContext> {
 public:
  using Handle = detail::Handle<ContainerContext>;

 public:
  template <typename... Args>
  static std::shared_ptr<ContainerContext> create(Args &&... args) {
    return make_shared(Container::create(std::forward<Args>(args)...));
  }

  template <typename... Args>
  Handle createProcessGroup(Args &&... args) {
    return Handle(
        shared_from_this(),
        registerChildContext(ProcessGroupContext::make_shared(
            member().createProcessGroup(std::forward<Args>(args)...))));
  }

 private:
  template <typename... Args>
  static std::shared_ptr<ContainerContext> make_shared(Args &&... args) {
    std::shared_ptr<ContainerContext> ctx(
        new ContainerContext(std::forward<Args>(args)...));
    return ctx;
  }

  BUNSAN_FORWARD_EXPLICIT_CONSTRUCTOR(ContainerContext, Context)
};

using ContainerContextPointer = std::shared_ptr<ContainerContext>;
using ProcessGroupHandle = ContainerContext::Handle;

}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
