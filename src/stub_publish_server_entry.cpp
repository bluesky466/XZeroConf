#include "stub_publish_server_entry.h"
#include "stub_publish_service_entry.h"

#include <cassert>

namespace xzc {
StubPublishServerEntry::StubPublishServerEntry(bool enable)
        : enable_(enable), is_start_(false) {
}

void StubPublishServerEntry::PublishService(
    const Service& service, const PublishServiceEntry::Callback& callback,
    const PublishCallback& on_success, const PublishCallback& on_error) {
    assert(is_start_ && "StubPublishServerEntry is not start");
    auto entry =
        new StubPublishServiceEntry(service, callback, on_success, on_error);
    entry->SetPublishFinished(enable_);
    entry->OnPublished();
}

void StubPublishServerEntry::Start() {
    is_start_ = true;
}

void StubPublishServerEntry::Stop() {
    is_start_ = false;
}

};  // xzc
