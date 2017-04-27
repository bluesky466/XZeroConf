#ifndef PUBLISH_SERVER_ENTRY_H_
#define PUBLISH_SERVER_ENTRY_H_

#include <map>
#include <string>

#include "publish_service_entry.h"
#include "service.h"

namespace xzc {
class PublishServerEntry {
public:
    typedef std::map<std::string, Service> Services;

public:
    virtual void PublishService(const Service& service,
                                const PublishServiceEntry::Callback& callback,
                                const PublishCallback& on_success,
                                const PublishCallback& on_error) = 0;

    virtual ~PublishServerEntry() {
    }

    virtual void Start() = 0;

    virtual void Stop() = 0;
};

}  // xzc

#endif  // STUB_PUBLISH_SERVER_ENTRY_H_
