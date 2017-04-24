#include "catch.hpp"

#include "publish_server.h"
#include "stub_publish_server_entry.h"
#include "service.h"

using std::make_shared;
using xzc::Service;
using xzc::PublishServer;
using xzc::StubPublishServerEntry;

SCENARIO("test publish server", "[publish-server]") {
    bool is_on_success = false;
    auto on_success = [&](const Service& service) { is_on_success = true; };

    bool is_on_error = false;
    auto on_error = [&](const Service& service) { is_on_error = true; };

    Service service("service", "_http._tcp");

    GIVEN("a publish server with enable stub publish entry") {
        PublishServer server(make_shared<StubPublishServerEntry>(true));

        WHEN("publish a service") {
            server.PublishService(service, on_success, on_error);

            THEN("publish successfully") {
                REQUIRE(is_on_success);
                REQUIRE_FALSE(is_on_error);
            }

            THEN("publish one service") {
                auto services = server.GetServices();
                REQUIRE(services.size() == 1);
                REQUIRE(services["service"] == service);
            }
        }
    }

    GIVEN("a publish server with disable stub publish entry") {
        PublishServer server(make_shared<StubPublishServerEntry>(false));

        WHEN("publish a service") {
            server.PublishService(service, on_success, on_error);

            THEN("publish unsuccessfully") {
                REQUIRE_FALSE(is_on_success);
                REQUIRE(is_on_error);
            }

            THEN("no published service") {
                auto services = server.GetServices();
                REQUIRE(services.empty());
            }
        }
    }

	GIVEN("a published service") {
        PublishServer server(make_shared<StubPublishServerEntry>(true));
        server.PublishService(service, on_success, on_error);

		THEN("stop publish") {
			bool ret = server.StopPublished(service);

			THEN("servie is stop published") {
				auto services = server.GetServices();
                REQUIRE(ret);
                REQUIRE(services.empty());
			}
		}
	}
}
