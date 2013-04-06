/*
 * collections.c
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdlib.h>
#include <utils/collections.h>

unsigned int calculate_hash_code_for_string(void* key);

unsigned int calculate_hash_code_for_sint(void* key);

unsigned int calculate_hash_code_for_usint(void* key);

unsigned int calculate_hash_code_for_int(void* key);

unsigned int calculate_hash_code_for_uint(void* key);

unsigned int calculate_hash_code_for_ulong(void* key);

unsigned int calculate_hash_code_for_long(void* key);

bool compare_string_keys(void* key1, void* key2);

bool compare_integer_keys(void* key1, void* key2);

struct hash_map* create_hash_map(
    unsigned int hash_size, enum types key_type, enum types value_type)
{
  struct hash_map* map = malloc(sizeof(struct hash_map));
  map->key_type = key_type;
  map->value_type = value_type;
  map->size = 0;
  map->hash_size = hash_size;
  map->hash = malloc(sizeof(struct hash_map_item) * hash_size);
  switch(key_type)
  {
    case STRING:
      map->calculate_hash_code = calculate_hash_code_for_string;
      map->compare_keys = compare_string_keys;
      break;
    case USINT:
      map->calculate_hash_code = calculate_hash_code_for_usint;
      map->compare_keys = compare_integer_keys;
      break;
    case SINT:
      map->calculate_hash_code = calculate_hash_code_for_sint;
      map->compare_keys = compare_integer_keys;
      break;
    case UINT:
      map->calculate_hash_code = calculate_hash_code_for_uint;
      map->compare_keys = compare_integer_keys;
      break;
    case INT:
      map->calculate_hash_code = calculate_hash_code_for_int;
      map->compare_keys = compare_integer_keys;
      break;
    case ULONG:
      map->calculate_hash_code = calculate_hash_code_for_ulong;
      map->compare_keys = compare_integer_keys;
      break;
    case LONG:
      map->calculate_hash_code = calculate_hash_code_for_long;
      map->compare_keys = compare_integer_keys;
      break;
  }
  return map;
}

struct hash_map_item* get_item(struct hash_map* map, void* key, bool creation)
{
  unsigned int hash_code = map->calculate_hash_code(key);
  struct hash_map_item* result = NULL;
  unsigned int index = hash_code % map->hash_size;
  struct hash_map_item* first = map->hash[index];
  struct hash_map_item* item = NULL;
  if (first) {
    for (item = first; item; item = item->next) {
      if (item->previous != NULL && map->compare_keys(key, item->key)) {
        result = item;
        break;
      }
    }
  }
  if (result == NULL && creation) {
    result = malloc(sizeof(struct hash_map_item));
    result->key = key;
    result->previous = NULL;
    result->next = NULL;
    if (item == NULL) {
      item = malloc(sizeof(struct hash_map_item));
      item->previous = NULL;
      map->hash[index] = item;
      item->next = result;
    }
    result->previous = item;
  }

  return result;
}

/*
 * The key and value arguments must be a reference to
 * dynamically allocated memory or a value
 */
int add_to_hash_map(struct hash_map* map, void* key, void* value)
{
  struct hash_map_item* item = get_item(map, key, TRUE);
  item->value = value;
  return 0;
}

int remove_from_hash_map(struct hash_map* map, void* key)
{
  struct hash_map_item* item = get_item(map, key, FALSE);
  if (item) {
    item->previous->next = item->next;
    free(item);
  }
  return 0;
}

struct hash_map_result* get_value_from_hash_map(
    struct hash_map* map, void* key)
{
  struct hash_map_item* item = get_item(map, key, FALSE);
  struct hash_map_result* result = malloc(sizeof(struct hash_map_result));
  if (item != NULL) {
    result->exists = TRUE;
    result->value = item->value;
  }
  else {
    result->exists = FALSE;
  }
  return result;
}

int free_hash_map(struct hash_map* hash_map)
{
  return 0;
}

unsigned int calculate_hash_code_for_string(void* key)
{
  unsigned int hash = 0;
  unsigned char* string = key;
  for (; *string != NULL; string++) {
    hash = 31*hash + *string;
  }
  return hash;
}

unsigned int calculate_hash_code_for_sint(void *key)
{
  return abs((short int)key);
}

unsigned int calculate_hash_code_for_usint(void *key)
{
  return (unsigned short int)key;
}

unsigned int calculate_hash_code_for_int(void *key)
{
  return abs((int)key);
}

unsigned int calculate_hash_code_for_uint(void *key)
{
  return (unsigned int)key;
}

//TODO resolve a problem with void pointer and long sizes on 32bit systems
unsigned int calculate_hash_code_for_long(void *key)
{
  return labs((long)key);
}

unsigned int calculate_hash_code_for_ulong(void *key)
{
  return (unsigned long)key;
}

bool compare_string_keys(void* key1, void* key2)
{
  if (strncmp(key1, key2, MAX_STRING_LENGTH) == 0)
    return TRUE;
  else
    return FALSE;
}

bool compare_integer_keys(void* key1, void* key2)
{
  if (key1 == key2)
    return TRUE;
  else
    return FALSE;
}
