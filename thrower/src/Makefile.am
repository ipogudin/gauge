AM_CPPFLAGS = -std=c++11 -I$(top_srcdir)/deps/usr/include
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib
LIBS = \
-lPocoFoundation -lPocoUtil\
-lPocoXML -lPocoNet

bin_PROGRAMS = throwerd
throwerd_SOURCES = throwerd.cpp

throwerd_LDADD = \
  libthrower.a

noinst_LIBRARIES = libthrower.a

libthrower_a_SOURCES = \
  commons.h \
  Thrower.h Thrower.cpp \
  Configuration.h Configuration.cpp \
  Logger.h Logger.cpp \
  Exception.h Exception.cpp \
  Manager.h Manager.cpp
  