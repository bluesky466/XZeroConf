#include "catch.hpp"

#include "avahi_publisher.h"

namespace xzc {

SCENARIO("test avahi publisher", "[AvahiPublisher]") {
    AvahiPublisher publisher;

    WHEN("check initialization") {
        THEN("simple poll loop") {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            REQUIRE(publisher.IsPollLoop());
        }
    }

    WHEN("start publisher") {
        publisher.Start();

        THEN("publisher running") {
            REQUIRE(publisher.IsRunning());
        }
    }
}

}  // xzc
