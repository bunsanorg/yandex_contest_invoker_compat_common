#pragma once

#include <yandex/contest/invoker/compat/detail/BasicContextChildren.hpp>

#include <boost/assert.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace detail
{
    template <typename MemberPointer_, typename ChildContext_>
    class BasicContext: public BasicContextChildren<ChildContext_>
    {
    public:
        typedef MemberPointer_ MemberPointer;
        typedef ChildContext_ ChildContext;
        typedef BasicContext<MemberPointer, ChildContext> Context;
        typedef typename MemberPointer::element_type Member;

    public:
        explicit BasicContext(const MemberPointer &member):
            member_(member)
        {
            BOOST_ASSERT(member_);
        }

        Member &member()
        {
            BOOST_ASSERT(member_);
            return *member_;
        }

    private:
        MemberPointer member_;
    };
}}}}}
