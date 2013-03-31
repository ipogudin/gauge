/*
 * collections.c
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdlib.h>
#include <utils/collections.h>

unsigned int calculate_hash_code_for_string(
    struct hash_map* this, void *value);

unsigned int calculate_hash_code_for_integer(
    struct hash_map* this, void *value);


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
      break;
    default:
      map->calculate_hash_code = calculate_hash_code_for_integer;
      break;
  }
  return map;
}

int add_to_hash_map(struct hash_map* hash_map, void* key, void* value)
{
  return 0;
}

int remove_from_hash_map(struct hash_map* hash_map, void* key)
{
  return 0;
}

int free_hash_map(struct hash_map* hash_map)
{
  return 0;
}

unsigned int calculate_hash_code_for_string(
    struct hash_map* this, void *value)
{
  unsigned int hash = 0;
  unsigned char* string = value;
  for (; *string != NULL; string++)
  {
    hash = 31*hash + *string;
  }
  return hash;
}

unsigned int calculate_hash_code_for_integer(
    struct hash_map* this, void *value)
{
  return abs(value);
}
