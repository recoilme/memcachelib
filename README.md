## BUILD https://github.com/xant/libhl
```
git submodule init
git submodule update
cd ./deps/ && autoreconf --install
cd build
../configure
make
cp ./build/libhl.a ../
cd .. && cd ..
```

## BUILD lru
```
//gcc -I./deps/src -L./deps/build/.libs -o lru lru.c
gcc -I./deps/src -L. -lhl -o lru lru.c
```

## Usage
```
cache = create_cache(3);
char *key = "hello";
char *val = "world";
int res = 0;

res = set(cache,key,&val,sizeof(val));
assert(res==0);
size_t size;
size = get(cache,key,&val);
printf("get return \tval:%.*s\n",(int)size,val);

```