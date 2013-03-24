/*
 * collections.h
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef COLLECTIONS_H_
#define COLLECTIONS_H_

struct hash_map_item {
  void* value;
};

struct hash_map {
  unsigned short size;
  unsigned short* hash;
};

extern struct hash_map* create_hash_map(unsigned short size);

#endif /* COLLECTIONS_H_ */
