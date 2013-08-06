#pragma once

#include <yandex/contest/invoker/Error.hpp>

#include <unordered_map>

#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace detail
{
    typedef std::size_t Id;

    struct InvalidIdError: virtual Error
    {
        typedef boost::error_info<struct idTag, Id> id;
    };

    template <typename ChildContext>
    class BasicContextChildren: private boost::noncopyable
    {
    private:
        typedef BasicContextChildren<ChildContext> ContextChildren;
        typedef std::shared_ptr<ChildContext> ChildContextSharedPtr;
        typedef std::unordered_map<Id, ChildContextSharedPtr> Map;

    public:
        Id registerChildContext(std::shared_ptr<ChildContext> &&context)
        {
            const Id id = newId_++; // allocate unique id
            BOOST_ASSERT(children_.find(id) == children_.end());
            children_[id] = std::move(context);
            return id;
        }

        ChildContext &child(const Id id)
        {
            return *(index(id)->second);
        }

        void destroyChild(const Id id)
        {
            children_.erase(index(id));
        }

    private:
        typename Map::iterator index(const Id id)
        {
            const typename Map::iterator iter = children_.find(id);
            if (iter == children_.end())
                BOOST_THROW_EXCEPTION(InvalidIdError() << InvalidIdError::id(id));
            return iter;
        }

    private:
        Id newId_ = 0;
        Map children_;
    };

    template <>
    class BasicContextChildren<void> {};
}}}}}
