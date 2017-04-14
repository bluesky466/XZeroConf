AM_CPPFLAGS = -I$(top_srcdir)/tests \
			  -I$(top_srcdir)/src \
			  -std=c++11

bin_PROGRAMS = tests

tests_SOURCES = test_service.cpp

tests_LDADD = $(top_builddir)/src/service.o

