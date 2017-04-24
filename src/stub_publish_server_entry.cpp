#include "stub_publish_server_entry.h"
#include "stub_publish_service_entry.h"

namespace xzc {
StubPublishServerEntry::StubPublishServerEntry(bool enable) : enable_(enable) {
}

void StubPublishServerEntry::PublishService(
    const Service& service, const PublishServiceEntry::Callback& callback,
    const PublishCallback& on_success, const PublishCallback& on_error) {
    auto entry =
        new StubPublishServiceEntry(service, callback, on_success, on_error);
    entry->SetPublishFinished(enable_);
    entry->OnPublished();
}
};  // xzc
