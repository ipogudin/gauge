
CFLAGS = @CFLAGS@ -I$(top_srcdir)/include

TESTS = \
  check_platform \
  check_errors \
  check_collections

check_PROGRAMS = \
  check_platform \
  check_errors \
  check_collections

check_platform_SOURCES = \
  check_platform.c \
  $(top_builddir)/include/platform.h \
  $(top_builddir)/include/tests/tests.h
check_platform_CFLAGS = @CHECK_CFLAGS@
check_platform_LDADD = \
  $(top_srcdir)/src/utils/libutils.a \
  @CHECK_LIBS@

check_errors_SOURCES = \
  check_errors.c \
  $(top_builddir)/include/errors.h \
  $(top_builddir)/include/tests/tests.h
check_errors_CFLAGS = @CHECK_CFLAGS@
check_errors_LDADD = \
  $(top_srcdir)/src/utils/libutils.a \
  @CHECK_LIBS@

check_collections_SOURCES = \
  check_collections.c \
  $(top_builddir)/include/collections.h \
  $(top_builddir)/include/tests/tests.h
check_collections_CFLAGS = @CHECK_CFLAGS@
check_collections_LDADD = \
  $(top_srcdir)/src/utils/libutils.a \
  @CHECK_LIBS@