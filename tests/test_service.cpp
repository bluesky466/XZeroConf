#include "catch.hpp"

#include "service.h"

namespace xzc {

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
        THEN("name changed") {
            REQUIRE(service.GetName() == "new name");
        }
    }

    WHEN("set type") {
        service.SetType("_ipp._tcp");
        THEN("type changed") {
            REQUIRE(service.GetType() == "_ipp._tcp");
        }
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
        THEN("domain is setted") {
            REQUIRE(service.GetDomain() == "local");
        }
    }

    WHEN("set subtype") {
        service.SetSubType("subtype");
        THEN("subtype is setted") {
            REQUIRE(service.GetSubType() == "subtype");
        }
    }

    WHEN("set interface") {
        service.SetInterface(1);
        THEN("interface is setted") {
            REQUIRE(service.GetInterface() == 1);
        }
    }

    WHEN("set protocol") {
        service.SetProtocol(Protocol::kIPv6);
        THEN("protocol is setted") {
            REQUIRE(service.GetProtocol() == Protocol::kIPv6);
        }
    }

	WHEN("compare two services with the same name") {
    	Service service_cmp("service", "_http._tcp");
		THEN("tow services equal") {
			REQUIRE(service == service_cmp);
		}
	}

	WHEN("compare two services with the different name") {
    	Service service_cmp1("service", "_http._tcp");
    	Service service_cmp2("service", "_ipp._tcp");
    	Service service_cmp3("other service", "_http._tcp");
		THEN("tow services equal") {
			REQUIRE(service == service_cmp1);
			REQUIRE_FALSE(service == service_cmp2);
			REQUIRE_FALSE(service == service_cmp3);
		}
	}
}

}  // xzc
