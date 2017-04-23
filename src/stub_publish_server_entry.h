#ifndef STUB_PUBLISH_SERVER_ENTRY_H_
#define STUB_PUBLISH_SERVER_ENTRY_H_

#include <map>
#include <string>

#include "publish_service_entry.h"
#include "service.h"

namespace xzc {
class StubPublishServerEntry {
public:
    typedef std::map<std::string, Service> Services;

public:
    StubPublishServerEntry(bool enable);

    void PublishService(const Service& service,
                        const PublishServiceEntry::Callback& callback,
                        const PublishCallback& on_success,
                        const PublishCallback& on_error);

private:
    bool enable_;
};

}  // xzc

#endif  // STUB_PUBLISH_SERVER_ENTRY_H_
