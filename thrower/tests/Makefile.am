SUBDIRS = utils

CFLAGS = @CFLAGS@ -I$(top_srcdir)/include

TESTS = check_configuration
check_PROGRAMS = check_configuration
check_configuration_SOURCES = \
	check_configuration.c \
	$(top_builddir)/include/configuration.h \
	$(top_builddir)/include/tests/tests.h
check_configuration_CFLAGS = @CHECK_CFLAGS@
check_configuration_LDADD = \
  $(top_srcdir)/src/libconfiguration.a \
  @CHECK_LIBS@