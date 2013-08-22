AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include \
-I$(top_srcdir)/generated-src
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib
LIBS = \
-lPocoFoundation -lPocoUtil\
-lPocoXML -lPocoNet\
-lprotobuf

bin_PROGRAMS = throwerd
throwerd_SOURCES = throwerd.cpp

throwerd_LDADD = \
  $(top_srcdir)/src/libthrower.a \
  $(top_srcdir)/generated-src/libproto.a

noinst_LIBRARIES = libthrower.a

libthrower_a_SOURCES = \
  commons.h \
  Thrower.h Thrower.cpp \
  Configuration.h Configuration.cpp \
  Logger.h Logger.cpp \
  Exception.h Exception.cpp \
  Manager.h Manager.cpp \
  MessageTransport.h
  