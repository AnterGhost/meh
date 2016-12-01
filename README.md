# meh


build with

```g++ -std=c++14 -ldl -lSDL2 -shared -o test.so -fPIC test.cpp -fpermissive```

launch with
```LD_PRELOAD=test.so ./csgo.sh -steam```
