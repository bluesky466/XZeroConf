#include "test_xzeroconf.h"
#include "service.h"

using namespace xzc;

SCENARIO("test service", "[service]") {
    Service service("service", "_http._tcp");
    WHEN("check initialization") {
        THEN("service init with default") {
            REQUIRE(service.GetName() == "service");
            REQUIRE(service.GetType() == "_http._tcp");
            REQUIRE(service.GetTXT().empty());
            REQUIRE(service.GetInterface() == 0);
            REQUIRE(service.GetProtocol() == Protocol::kNoSpec);
        };
    }

    WHEN("set name") {
        service.SetName("new name");
        THEN("name changed") { REQUIRE(service.GetName() == "new name"); }
    }

    WHEN("set type") {
        service.SetType("_ipp._tcp");
        THEN("type changed") { REQUIRE(service.GetType() == "_ipp._tcp"); }
    }

    WHEN("add txt record") {
        service.SetTXTRecord("keyA", "valueA");
        service.SetTXTRecord("keyB", "valueB");

        THEN("txt record increased") {
            REQUIRE(service.GetTXT().size() == 2);
            REQUIRE(service.GetTXTRecord("keyA") == "valueA");
            REQUIRE(service.GetTXTRecord("keyB") == "valueB");
        }
    }

    WHEN("set domain") {
        service.SetDomain("local");
        THEN("domain is setted") { REQUIRE(service.GetDomain() == "local"); }
    }

    WHEN("set subtype") {
        service.SetSubType("subtype");
        THEN("subtype is setted") {
            REQUIRE(service.GetSubType() == "subtype");
        }
    }

    WHEN("set interface") {
        service.SetInterface(1);
        THEN("interface is setted") { REQUIRE(service.GetInterface() == 1); }
    }

    WHEN("set protocol") {
        service.SetProtocol(Protocol::kIPv6);
        THEN("protocol is setted") {
            REQUIRE(service.GetProtocol() == Protocol::kIPv6);
        }
    }
}
