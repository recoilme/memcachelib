#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lru.h"

//gcc -I./deps/src -L./deps/build/.libs -o lru lru.c
memcache cacheholder;

void cache_print(memcache * cache,char * msg) {
    printf("print:%s\n",msg);
    size_t cnt = list_count(cache->list)-1;
    for (int i = cnt; i >= 0; i--) {
        printf("key:%s\n",list_pick_value(cache->list,i));
    }
}

int main(int argc, char **argv) {
    memcache * cache;
    cache = create_cache(3);
    char *key = "hello";
    char *val = "world";
    int res = 0;

    res = set(cache,key,&val,sizeof(val));
    assert(res==0);
    size_t size;
    size = get(cache,key,&val);
    printf("get return \tval:%.*s\n",(int)size,val);

    char *key2 = "hello";
    char *val2 = "world2";

    res = set(cache,key2,&val2,sizeof(val));
    assert(res==0);
    size = get(cache,key,&val);
    printf("get return \tval:%.*s\n",(int)size,val);

    cache_print(cache,"1");
    res = set(cache,key,&val,sizeof(val));
    
    for (int i = 1; i <= 4; i++) {
        char *key = malloc(100);
        char *val = malloc(100);
        sprintf(key, "key%d", i);
        sprintf(val, "val%d", i);
        res = set(cache,key,&val,sizeof(val));
        assert(res==0);
    }

    cache_print(cache,"after insert");
    size = get(cache,"key3\0",&val);
    cache_print(cache,"after get key3");
    char *key18 = "k18";
    char *val18 = "v18";
    res = set(cache,key18,&val18,sizeof(val18));
    cache_print(cache,"after set key18");
    return(0);
}


void destroy(memcache * cache) {
    list_destroy(cache->list);
    ht_destroy(cache->table);
    
}
memcache * create_cache(size_t capacity) {
    assert(capacity>0);
    cacheholder.list = list_create();
    cacheholder.table = ht_create(256, 0, NULL);
    cacheholder.capacity = capacity;
    return &cacheholder;
}

int slice_iterator_callback(void *item, size_t idx, void *user) {
    if (strcmp((char *)user,(char *)item) == 0) {
        return -2;//delete key if found
    }
    else {
        return 1;
    }
}

int list_delkey(linked_list_t * list, char * key) {
    slice_t *slice = slice_create(list, 0, list_count(list));
    return slice_foreach_value(slice, slice_iterator_callback, key);
}

int table_delkey(hashtable_t * table, char * key) {
    return ht_delete(table,key,sizeof(key),NULL,NULL);
}

int trimtosize(memcache * cache) {
    int res = 0;
    if (list_count(cache->list)>cache->capacity) {
        //pick end remove first value
        char *key =list_fetch_value(cache->list,0);
        if (key != NULL) {
            res = table_delkey(cache->table,key);
        }
        else {
            res = -1;
        }
        printf("trim list to size:%zu\n",list_count(cache->list));
        printf("trim table to size:%zu\n",ht_count(cache->table));
    } 
    return res;
}

int set(memcache * cache, char * key, char ** value, int valueLen) {
    printf("set\tkey:%s\tval:%.*s\n",key,valueLen,*value);
    //delete key from list if exists
    list_delkey(cache->list, key);
    //add 2 tail
    int res = list_push_value(cache->list, key);
    if (res == -1) {
        return res;
    }
    else {
        res = ht_set(cache->table, key, sizeof(key), *value, valueLen);
        if (res == 0) {
            res = trimtosize(cache);
        }
        else {
            list_pop_value(cache->list);//remove from tail
        }
    }
    
    return res;
}

size_t get(memcache * cache, char * key, char ** value) {
    size_t dlen = -1;
    char *val = ht_get(cache->table, key, sizeof(key),&dlen);
    printf("get\tval:%.*s\n",(int)dlen,val);
    //remove key
    list_delkey(cache->list,key);
    //add 2 tail
    list_push_value(cache->list, key);
    *value = val;
    return dlen;
}