#include "lru.h"
#include <linklist.h>

//gcc -I./deps/src -L./deps/build/.libs -o lru lru.c
memcache cacheholder;

int main(int argc, char **argv) {
    memcache * cache;
    cache = create_cache();
    char *v = "3434";
    set(cache,"1",&v,4);
    char *vv = "";
    get(cache,"1",vv);
    printf("val_main:%s\n",vv);
}


memcache * create_cache() {
    cacheholder.list = list_create();
    cacheholder.table = ht_create(256, 0, NULL);
    return &cacheholder;
}

void set(memcache * cache, char * key, char ** value, int valueLen) {
    ht_set(cache->table, key, sizeof(key), *value, valueLen);
}

bool get(memcache * cache, char * key, char * value) {
    size_t dlen;
    value = ht_get(cache->table, key, sizeof(key),&dlen);
    printf("val:%.*s\n",(int)dlen,value);
    return false;
}