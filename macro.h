#pragma once

#include <stdio.h>

#define MAIN() \
  int main()
#define MAIN_EX(argc, argv) \
  int main(int argc, char *argv[])

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))

#define dimension_of(x) (sizeof(x)/sizeof(*x))

#define FORWARD_FOR(i, s, e)  for(size_t i=s,__n=e;i<__n;++i)
#define BACKWARD_FOR(i, s, e) for(size_t i=s,__n=e;i>__n;--i)

#define LOG(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIGY(x)

#define _CONCAT(x,y) x##y
#define CONCAT(x,y) _CONCAT(x,y)

#define _ARGS_17(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...) _16
#define ARGS_LEN(...) _ARGS_17(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)