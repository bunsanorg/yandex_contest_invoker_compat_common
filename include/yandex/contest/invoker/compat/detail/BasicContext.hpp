#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContextChildren.hpp>

#include <boost/assert.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace detail {

template <typename MemberPointer_, typename ChildContext_>
class BasicContext : public BasicContextChildren<ChildContext_> {
 public:
  using MemberPointer = MemberPointer_;
  using ChildContext = ChildContext_;
  using Context = BasicContext<MemberPointer, ChildContext>;
  using Member = typename MemberPointer::element_type;

 public:
  explicit BasicContext(const MemberPointer &member) : member_(member) {
    BOOST_ASSERT(member_);
  }

  Member &member() {
    BOOST_ASSERT(member_);
    return *member_;
  }

 private:
  MemberPointer member_;
};

}  // namespace detail
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
