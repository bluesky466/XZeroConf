AM_CPPFLAGS = -I$(top_srcdir)/src \
			  -I$(top_srcdir)/third_party \
			  -std=c++11

bin_PROGRAMS = XZeroConf

XZeroConf_SOURCES = main.cpp \
					service.cpp \
					publish_service_entry.cpp \
					stub_publish_service_entry.cpp \
					stub_publish_server_entry.cpp \
					publish_server.cpp

XZeroConf_LDADD = -lpthread \
				  -lavahi-client \
				  -lavahi-common

