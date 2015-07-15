#pragma once

#include <yandex/contest/invoker/Error.hpp>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {

struct Error : virtual invoker::Error {};

}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
