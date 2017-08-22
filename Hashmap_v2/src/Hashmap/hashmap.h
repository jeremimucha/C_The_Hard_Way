#ifndef MYHASHMAP_H_
#define MYHASHMAP_H_

#include <stdint.h>
#include <Hashmap/darray.h>
#include <Hashmap/bstrlib.h>

#define DEFAULT_NUM_BUCKETS 100
typedef int(*Hashmap_compare)(void* a, void* b);
typedef uint32_t(*Hashmap_hash)(void* key);

typedef bstring Key;
typedef bstring Value;

typedef struct Hashmap{
    DArray* buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode{
    Key key;
    Value data;
    uint32_t hash;
} HashmapNode;

typedef int(*Hashmap_traverse_cb)(HashmapNode* node);

Hashmap* Hashmap_create(Hashmap_compare compare, Hashmap_hash);
void Hashmap_destroy(Hashmap* map);

int Hashmap_set(Hashmap* map, Key key, Value data);
Value Hashmap_get(Hashmap* map, Key key);

int Hashmap_traverse(Hashmap* map, Hashmap_traverse_cb traverse_cb);

Value Hashmap_delete(Hashmap* map, Key key);

#endif
