AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib \
-lPocoFoundation -lPocoUtil\
-lPocoXML

bin_PROGRAMS = throwerd
throwerd_SOURCES = throwerd.cpp

throwerd_LDADD = \
  libthrower.a \
  libconfiguration.a \
  liblogger.a

noinst_LIBRARIES = libthrower.a \
  libconfiguration.a \
  liblogger.a

libthrower_a_SOURCES = \
  Thrower.h Thrower.cpp

libconfiguration_a_SOURCES = \
  Configuration.h Configuration.cpp

liblogger_a_SOURCES = \
  Logger.h Logger.cpp