#include "catch.hpp"

#include "avahi_publish_server_entry.h"

using xzc::Service;
using xzc::PublishServiceEntry;
using xzc::AvahiPublishServerEntry;

SCENARIO("test publish avahi", "publish-avahi") {
    PublishServiceEntry* service_entry;
    auto on_result = [&](PublishServiceEntry* entry) {
        if (entry->IsPublished()) {
            entry->OnSuccess();
        } else {
            entry->OnError();
        }
        service_entry = entry;
    };

    bool is_on_success = false;
    auto on_success = [&](const Service& service) { is_on_success = true; };

    bool is_on_error = false;
    auto on_error = [&](const Service& service) { is_on_error = true; };

    Service service("service", "_http._tcp");

    GIVEN("a started avahi publish server entry without stop") {
        AvahiPublishServerEntry entry;
        entry.Start();
    }

    GIVEN("a started avahi publish server entry with stop") {
        AvahiPublishServerEntry entry;
        entry.Start();
		entry.Stop();
    }

}
