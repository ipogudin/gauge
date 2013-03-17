/*
 * check_configuration.c
 *
 *  Created on: Mar 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <tests/tests.h>
#include <configuration.h>

START_TEST(test_default_confiuration)

END_TEST

BEGIN
  SUITE("Configuration")
    CASE("Core")
      TEST(test_default_confiuration)
    END_CASE
  END_SUITE
END
