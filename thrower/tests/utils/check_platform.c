/*
 * check_configuration.c
 *
 *  Created on: Mar 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <tests/tests.h>
#include <utils/platform.h>

START_TEST(test_platform)
{

}
END_TEST

BEGIN
  SUITE("Platform")
    CASE("Core")
      TEST(test_platform)
    END_CASE
  END_SUITE
END
