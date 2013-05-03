AM_CPPFLAGS = -std=c++0x -I$(top_srcdir)/deps/usr/include
AM_LDFLAGS = -L$(top_srcdir)/deps/usr/lib \
-lPocoFoundation -lPocoUtil\
-lPocoXML

bin_PROGRAMS = throwerd
throwerd_SOURCES = throwerd.cpp \
  Thrower.h Thrower.cpp \
  Configuration.h Configuration.cpp