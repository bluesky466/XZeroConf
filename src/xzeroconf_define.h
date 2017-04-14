#ifndef XZEROCONF_DEFINE_H_
#define XZEROCONF_DEFINE_H_

#include <map>
#include <string>

namespace xzc {

using TXT = std::map<std::string, std::string>;

enum class Protocol {
    kNoSpec = 0,
    kIPv4 = 1,
    kIPv6 = 2,
};

} // xzc
#endif  // XZEROCONF_DEFINE_H_
