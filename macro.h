#pragma once

#include <stdio.h>

#define MAIN() \
  int main()
#define _MAIN(argc, argv) \
  int main(int argc, char *argv[])

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
