#include <stdlib.h>
#include <stdio.h>
//#include "./deps/src/linklist.h"
//#include "./deps/src/hashtable.h"
#include "lru.h"

//gcc -o lru lru.c ./deps/build/.libs/linklist.o

int main(int argc, char **argv) {
    printf("hello\n");
    //linked_list_t *list = list_create();
}


cache2 * create_cache() {
    return NULL;
}
void set(cache2 * cache, char * key, char ** value, int valueLen) {
    printf("Set cache\n");
}
bool get(cache2 * cache, char * key, char ** value) {
    printf("Get cache\n");
    return false;
}