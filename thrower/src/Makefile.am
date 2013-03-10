AM_CFLAGS = -I$(top_srcdir)/include

SUBDIRS = utils

bin_PROGRAMS = throwerd
throwerd_SOURCES = \
  throwerd.c

throwerd_LDADD = \
  libconfiguration.a \
  utils/libutils.a

noinst_LIBRARIES = libconfiguration.a
libconfiguration_a_SOURCES = \
  configuration.c \
  $(top_srcdir)/include/configuration.h