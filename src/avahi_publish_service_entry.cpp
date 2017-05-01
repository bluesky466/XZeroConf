#include "avahi_publish_service_entry.h"

namespace xzc {

AvahiPublishServiceEntry::AvahiPublishServiceEntry(
    const Service& service, const Callback& callback,
    const PublishCallback& on_success, const PublishCallback& on_error)
        : PublishServiceEntry(service, callback, on_success, on_error) {
}

bool AvahiPublishServiceEntry::StopPublished() {
	return true;
}

}  // xzc
