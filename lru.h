#include <linklist.h>
#include <hashtable.h>

typedef struct {
    linked_list_t* list;
    hashtable_t* table;
    size_t capacity;
} memcache;

memcache * create_cache(size_t capacity);

int set(memcache * cache, char * key, char ** value, int valueLen);

size_t get(memcache * cache, char * key, char ** value);

void destroy(memcache * cache);