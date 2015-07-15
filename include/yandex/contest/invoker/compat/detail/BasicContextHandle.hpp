#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContext.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace detail {

struct InvalidHandleError : virtual Error {};

template <typename Context_>
class BasicContextHandle {
 public:
  using ContextHandle = BasicContextHandle<Context_>;
  using Context = Context_;
  using ChildContext = typename Context::ChildContext;
  using Member = typename ChildContext::Member;
  using ContextSharedPtr = std::shared_ptr<Context>;
  using ContextWeakPtr = std::weak_ptr<Context>;

 public:
  BasicContextHandle(const ContextHandle &) = default;
  BasicContextHandle &operator=(const ContextHandle &) = default;

  void destroy() {
    ContextSharedPtr ctx = context_.lock();
    if (ctx) ctx->destroyChild(id_);
  }

  explicit operator bool() const { return !context_.expired(); }

 protected:
  BasicContextHandle() = default;

  BasicContextHandle(const ContextWeakPtr &context, const Id id)
      : context_(context), id_(id) {}

  ChildContext &context() {
    ContextSharedPtr ctx = context_.lock();
    if (!ctx) BOOST_THROW_EXCEPTION(InvalidHandleError());
    return ctx->child(id_);
  }

  Member &member() { return context().member(); }

 private:
  ContextWeakPtr context_;
  Id id_ = 0;
};

}  // namespace detail
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
