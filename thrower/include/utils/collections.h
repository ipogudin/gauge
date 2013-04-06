/*
 * collections.h
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_

#include <stdlib.h>
#include <utils/commons.h>

//hash map to work with dynamically created variables
#define MAX_STRING_LENGTH 4096

struct hash_map_result {
  void* value;
  bool exists;
};

struct hash_map_item {
  void* key;
  void* value;
  struct hash_map_item* next;
  struct hash_map_item* previous;
};

struct hash_map {
  unsigned int size;
  unsigned int hash_size;
  struct hash_map_item** hash;
  unsigned int (*calculate_hash_code)(void *value);
  bool (*compare_keys)(void* key1, void* key2);
  enum types key_type;
  enum types value_type;
};

extern struct hash_map* create_hash_map(
    unsigned int hash_size, enum types key_type, enum types value_type);

extern int add_to_hash_map(struct hash_map* map, void* key, void* value);

extern int remove_from_hash_map(struct hash_map* map, void* key);

extern struct hash_map_result* get_value_from_hash_map(
    struct hash_map* map, void* key);

extern int free_hash_map(struct hash_map* map);
//end of hash map declaration

#endif /* COLLECTIONS_H_ */
