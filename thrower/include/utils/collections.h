/*
 * collections.h
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_

#include <utils/commons.h>

//hash map to work with dynamically created variables
struct hash_map_item {
  void* key;
  void* value;
  struct hash_map_item* next;
};

struct hash_map {
  unsigned int size;
  unsigned int hash_size;
  struct hash_map_item** hash;
  unsigned int (*calculate_hash_code)(struct hash_map* this, void *value);
  enum types key_type;
  enum types value_type;
};

extern struct hash_map* create_hash_map(
    unsigned int hash_size, enum types key_type, enum types value_type);

extern int add_to_hash_map(struct hash_map* hash_map, void* key, void* value);

extern int remove_from_hash_map(struct hash_map* hash_map, void* key);

extern int free_hash_map(struct hash_map* hash_map);
//end of hash map declaration

#endif /* COLLECTIONS_H_ */
