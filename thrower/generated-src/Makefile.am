AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib
LIBS = \
-lprotobuf

noinst_LIBRARIES = libgaugeproto.a

libgaugeproto_a_SOURCES = \
  gauge.pb.cc gauge.pb.h
  