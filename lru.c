#include "lru.h"
#include <linklist.h>

//gcc -I./deps/src -L./deps/build/.libs -o lru lru.c
cache2 p = {NULL,NULL};

int main(int argc, char **argv) {
    printf("hello\n");
    cache2 *c = create_cache();
    char * v = "34\0";
    set(c,"1",v,3);
}


cache2 * create_cache() {
    p.list = list_create();
    return &p;
}

void set(cache2 * cache, char * key, char * value, int valueLen) {
    printf("Set key:%s\n",key);
    printf("Set val:%s\n",value);
    //char *a = malloc((valueLen+1) * sizeof(char));
    //a = &value[1];
    //printf("size %d\n",sizeof(a));
    //printf("Set val:%s\n",&a);
}

bool get(cache2 * cache, char * key, char * value) {
    printf("Get cache\n");
    return false;
}