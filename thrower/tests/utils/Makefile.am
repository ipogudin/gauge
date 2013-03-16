
CFLAGS = @CFLAGS@ -I$(top_srcdir)/include

TESTS = check_platform
check_PROGRAMS = check_platform
check_platform_SOURCES = \
	check_platform.c \
	$(top_builddir)/include/platform.h \
	$(top_builddir)/include/tests/tests.h
check_platform_CFLAGS = @CHECK_CFLAGS@
check_platform_LDADD = \
  $(top_srcdir)/src/utils/libutils.a \
  @CHECK_LIBS@