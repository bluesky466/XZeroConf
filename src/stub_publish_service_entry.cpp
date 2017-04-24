#include "stub_publish_service_entry.h"

namespace xzc {
StubPublishServiceEntry::StubPublishServiceEntry(
    const Service& service, const Callback& callback,
    const PublishCallback& on_success, const PublishCallback& on_error)
        : PublishServiceEntry(service, callback, on_success, on_error) {
}

bool StubPublishServiceEntry::StopPublished() {
    SetPublishFinished(false);
	return true;
}
}  // xzc
