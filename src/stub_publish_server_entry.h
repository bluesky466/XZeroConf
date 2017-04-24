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

	virtual void Start();

	virtual void Stop();
private:
    bool enable_;
	bool is_start_;
};

}  // xzc

#endif  // STUB_PUBLISH_SERVER_ENTRY_H_
