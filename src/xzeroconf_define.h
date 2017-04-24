#ifndef XZEROCONF_DEFINE_H_
#define XZEROCONF_DEFINE_H_

#include <map>
#include <string>
#include <functional>

namespace xzc {

using TXT = std::map<std::string, std::string>;

enum class Protocol {
    kNoSpec = 0,
    kIPv4 = 1,
    kIPv6 = 2,
};

class Service;
typedef std::function<void(const Service&)> PublishCallback;

}  // xzc
#endif  // XZEROCONF_DEFINE_H_
