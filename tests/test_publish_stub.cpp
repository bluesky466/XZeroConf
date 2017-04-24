#include "catch.hpp"

#include "service.h"
#include "publish_service_entry.h"
#include "stub_publish_service_entry.h"
#include "stub_publish_server_entry.h"

using xzc::Service;
using xzc::PublishServiceEntry;
using xzc::StubPublishServerEntry;

SCENARIO("test publish stub", "[publish-stub]") {
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

    GIVEN("a enable publish server entry") {
        StubPublishServerEntry entry(true);

        WHEN("publish service") {
            entry.PublishService(service, on_result, on_success, on_error);

            THEN("publish successfully") {
                REQUIRE(service_entry != nullptr);
                REQUIRE(service_entry->IsPublished());
                REQUIRE(is_on_success);
                REQUIRE_FALSE(is_on_error);
            }
        }
    }

    GIVEN("a disable publish server entry") {
        StubPublishServerEntry entry(false);

        WHEN("publish service") {
            entry.PublishService(service, on_result, on_success, on_error);

            THEN("publish unsuccessfully") {
                REQUIRE(service_entry != nullptr);
                REQUIRE_FALSE(service_entry->IsPublished());
                REQUIRE_FALSE(is_on_success);
                REQUIRE(is_on_error);
            }
        }
    }

    GIVEN("a publish server with a published service") {
        StubPublishServerEntry entry(false);
        entry.PublishService(service, on_result, on_success, on_error);

        WHEN("stop publish the service") {
            service_entry->StopPublished();
            THEN("service is stop published") {
				REQUIRE_FALSE(service_entry->IsPublished());
            }
        }
    }
}
