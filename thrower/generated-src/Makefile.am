AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib
LIBS = \
-lprotobuf

noinst_LIBRARIES = libproto.a

libproto_a_SOURCES = \
  protocol.pb.cc protocol.pb.h
  