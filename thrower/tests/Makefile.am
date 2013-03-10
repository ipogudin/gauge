SUBDIRS = utils

TESTS = check_configuration
check_PROGRAMS = check_configuration
check_configuration_SOURCES = \
	check_configuration.c \
	$(top_builddir)/include/configuration.h
check_configuration_CFLAGS = @CHECK_CFLAGS@
check_configuration_LDADD = \
  $(top_srcdir)/src/libconfiguration.a \
  @CHECK_LIBS@