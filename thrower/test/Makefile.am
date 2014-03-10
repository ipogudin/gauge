AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include \
  -I$(top_srcdir)/src -I$(top_srcdir)/generated-src
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib
LIBS= \
-lPocoFoundation -lPocoUtil\
-lPocoXML -lPocoNet -lpthread\
-lprotobuf

bin_PROGRAMS = test
test_LDADD=\
  $(top_srcdir)/deps/usr/lib/libgmock.a \
  $(top_srcdir)/deps/usr/lib/libgtest.a \
  $(top_srcdir)/src/libthrower.a \
  $(top_srcdir)/generated-src/libgaugeproto.a
test_SOURCES = test.cpp \
  ConfigurationTest.cpp \
  ManagerTest.cpp \
  MessageTransportTest.cpp