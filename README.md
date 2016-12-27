** BUILD https://github.com/xant/libhl
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

** BUILD lru 
```
//gcc -I./deps/src -L./deps/build/.libs -o lru lru.c
gcc -I./deps/src -L. -lhl -o lru lru.c
```
