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