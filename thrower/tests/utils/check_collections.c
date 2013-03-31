/*
 * check_collections.c
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <stdlib.h>
#include <tests/tests.h>
#include <utils/strings.h>
#include <utils/collections.h>

#define MESSAGE_BUFFER_SIZE 256

START_TEST(test_hash_map_creation)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, STRING, INT);
  fail_unless(map != NULL, "A pointer must be defined after a map is created");
  fail_unless(map->key_type == STRING, "A key type must be STRING");
  fail_unless(map->value_type == INT, "A value type must be INT");
  fail_unless(map->size == 0, "Just created hash map must be empty");
  fail_unless(map->hash_size == HASH_SIZE, "Hash size must be 8");
  fail_unless(map->calculate_hash_code != NULL, "A hash function must be defined");
  free_hash_map(map);
END_TEST

START_TEST(test_calculation_hash_code_for_string)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, STRING, INT);
  unsigned int hash_code1 = map->calculate_hash_code(map, "string");
  unsigned int hash_code2 = map->calculate_hash_code(map, "string");
  unsigned int hash_code3 = map->calculate_hash_code(map, "test string");

  char* message1 = sformat(
      MESSAGE_BUFFER_SIZE,
      "Hash code of the same string must be equal  ('%u' != '%u')",
      hash_code1, hash_code2
      );
  fail_unless(hash_code1 == hash_code2, message1);

  char* message2 = sformat(
      MESSAGE_BUFFER_SIZE,
      "Hash code of different strings must be different ('%u' != '%u')",
      hash_code1, hash_code3);
  fail_unless(hash_code1 != hash_code3, message2);
  free(message2);

  free_hash_map(map);
END_TEST

BEGIN
  SUITE("Collections")
    CASE("HashMap")
      TEST(test_hash_map_creation)
      TEST(test_calculation_hash_code_for_string)
    END_CASE
  END_SUITE
END
