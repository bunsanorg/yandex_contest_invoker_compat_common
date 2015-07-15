#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContextHandle.hpp>

#include <bunsan/forward_constructor.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace detail {

template <typename Context_>
class Handle : public BasicContextHandle<Context_> {
 public:
  using Parent = BasicContextHandle<Context_>;

 public:
  using Parent::context;
  using Parent::member;

  BUNSAN_FORWARD_EXPLICIT_CONSTRUCTOR(Handle, Parent)
};

}  // namespace detail
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
