AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include \
  -I$(top_srcdir)/src
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib \
-lPocoFoundation -lPocoUtil\
-lPocoXML -lpthread

bin_PROGRAMS = test
test_LDADD=$(top_srcdir)/deps/usr/lib/libgmock_main.a \
  $(top_srcdir)/deps/usr/lib/libgmock.a \
  $(top_srcdir)/deps/usr/lib/libgtest.a
test_SOURCES = ConfigurationTest.cpp
  