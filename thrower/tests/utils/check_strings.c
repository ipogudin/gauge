/*
 * check_strings.c
 *
 *  Created on: Mar 31, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <stdlib.h>
#include <tests/tests.h>
#include <utils/strings.h>

START_TEST(test_sformat)
  char* s = sformat(32, "*%d%s*", 10, "string");
  fail_unless(strncmp(s, "*10string*", 20) == 0,
    "A sformat function must return a correct string");
  free(s);
END_TEST

BEGIN
  SUITE("Strings")
    CASE("Strings")
      TEST(test_sformat)
    END_CASE
  END_SUITE
END
