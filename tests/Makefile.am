AM_CPPFLAGS = -I$(top_srcdir)/tests \
			  -I$(top_srcdir)/src \
			  -I$(top_srcdir)/third_party \
			  -std=c++11

bin_PROGRAMS = tests

tests_SOURCES = test_xzeroconf.cpp \
				test_service.cpp \
				test_publish_stub.cpp

tests_LDADD = $(top_builddir)/src/service.o \
			  $(top_builddir)/src/publish_service_entry.o \
			  $(top_builddir)/src/stub_publish_service_entry.o \
			  $(top_builddir)/src/stub_publish_server_entry.o \
			  -lavahi-client \
			  -lavahi-common

