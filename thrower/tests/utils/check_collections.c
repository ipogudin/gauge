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
  fail_unless(map->calculate_hash_code != NULL,
      "A hash function must be defined");
  free_hash_map(map);
END_TEST

START_TEST(test_calculation_hash_code_for_string)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, STRING, INT);
  unsigned int hash_code1 = map->calculate_hash_code("string");
  unsigned int hash_code2 = map->calculate_hash_code("string");
  unsigned int hash_code3 = map->calculate_hash_code("test string");

  fail_unless(
      hash_code1 == hash_code2,
      "Hash code of the same string must be equal  ('%u' != '%u')",
      hash_code1, hash_code2);

  fail_unless(
      hash_code1 != hash_code3,
      "Hash code of different strings must be different ('%u' != '%u')",
      hash_code1, hash_code3);

  free_hash_map(map);
END_TEST

START_TEST(test_calculation_hash_code_for_uint)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, INT, INT);
  unsigned int hash_code1 = map->calculate_hash_code((unsigned int)1);
  unsigned int hash_code2 = map->calculate_hash_code((unsigned int)1);
  unsigned int hash_code3 = map->calculate_hash_code((unsigned int)3);

  fail_unless(
      hash_code1 == hash_code2,
      "A hash code of the same uint numbers must be equal  ('%u' != '%u')",
      hash_code1, hash_code2);


  fail_unless(
      hash_code1 != hash_code3,
      "A hash code of different uint numbers must be different ('%u' != '%u')",
      hash_code1, hash_code3);

  free_hash_map(map);
END_TEST

START_TEST(test_calculation_hash_code_for_int)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, INT, INT);
  unsigned int hash_code1 = map->calculate_hash_code(-1);
  unsigned int hash_code2 = map->calculate_hash_code(-1);
  unsigned int hash_code3 = map->calculate_hash_code(3);

  fail_unless(
      hash_code1 == hash_code2,
      "A hash code of the same int numbers must be equal  ('%u' != '%u')",
      hash_code1, hash_code2);

  fail_unless(
      hash_code1 != hash_code3,
      "A hash code of different int numbers must be different ('%u' != '%u')",
      hash_code1, hash_code3);

  free_hash_map(map);
END_TEST

START_TEST(test_adding_and_getting_key_value_pair)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, STRING, INT);
  char* key = sformat(
      MESSAGE_BUFFER_SIZE,
      "key1"
      );
  int value = 1000;
  add_to_hash_map(map, key, value);

  struct hash_map_result* result =  get_value_from_hash_map(map, key);
  fail_unless(
      result->exists,
      "The key [%s] doen't exists",
      key);

  int actual_value = result->value;
  fail_unless(
      value == actual_value,
      "The key [%s] doesn't correspond with the value [%d] \
but the actual value is [%d]",
      key, value, actual_value);
  free(result);

  free_hash_map(map);
END_TEST

START_TEST(test_adding_and_removing_key_value_pair)
  const unsigned int HASH_SIZE = 8;
  struct hash_map* map = create_hash_map(HASH_SIZE, STRING, INT);
  char* key = sformat(
        MESSAGE_BUFFER_SIZE,
        "key1"
        );
  int value = 1000;
  add_to_hash_map(map, key, value);
  remove_from_hash_map(map, key);

  struct hash_map_result* result =  get_value_from_hash_map(map, key);
  fail_unless(
      !result->exists,
      "The key [%s] must be removed",
      key);
  free(result);

  free_hash_map(map);
END_TEST

BEGIN
  SUITE("Collections")
    CASE("HashMap")
      TEST(test_hash_map_creation)
      TEST(test_calculation_hash_code_for_string)
      TEST(test_calculation_hash_code_for_uint)
      TEST(test_calculation_hash_code_for_int)
      TEST(test_adding_and_getting_key_value_pair)
      TEST(test_adding_and_removing_key_value_pair)
    END_CASE
  END_SUITE
END
