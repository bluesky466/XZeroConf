#ifndef STUB_PUBLISH_SERVICE_ENTRY_H_
#define STUB_PUBLISH_SERVICE_ENTRY_H_

#include "publish_service_entry.h"

namespace xzc {
class StubPublishServiceEntry : public PublishServiceEntry {
public:
    StubPublishServiceEntry(const Service& service, const Callback& callback,
                            const PublishCallback& on_success,
                            const PublishCallback& on_error);

    virtual void StopPublished();
};
}  // xzc

#endif  // STUB_PUBLISH_SERVICE_ENTRY_H_
