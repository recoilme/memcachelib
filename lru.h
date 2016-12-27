#include <stdlib.h>
#include <stdio.h>
#include <linklist.h>
#include <hashtable.h>

typedef struct {
    linked_list_t* list;
    hashtable_t* table; 
} memcache;

memcache * create_cache();

void set(memcache * cache, char * key, char ** value, int valueLen);

bool get(memcache * cache, char * key, char * value);