#ifndef STUB_PUBLISH_SERVER_ENTRY_H_
#define STUB_PUBLISH_SERVER_ENTRY_H_

#include "publish_server_entry.h"

namespace xzc {
class StubPublishServerEntry : public PublishServerEntry {
public:
    StubPublishServerEntry(bool enable);

    virtual void PublishService(const Service& service,
                        const PublishServiceEntry::Callback& callback,
                        const PublishCallback& on_success,
                        const PublishCallback& on_error);
private:
    bool enable_;
};

}  // xzc

#endif  // STUB_PUBLISH_SERVER_ENTRY_H_
