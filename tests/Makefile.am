AM_CPPFLAGS = -I$(top_srcdir)/tests \
			  -I$(top_srcdir)/src \
			  -I$(top_srcdir)/third_party \
			  -std=c++11

bin_PROGRAMS = tests

tests_SOURCES = test_xzeroconf.cpp \
				test_service.cpp \
				test_avahi_publisher.cpp

tests_LDADD = $(top_builddir)/src/service.o \
			  $(top_builddir)/src/avahi_publisher.o \
			  -lavahi-client \
			  -lavahi-common

