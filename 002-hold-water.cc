#include <vector>
#include "macro.h"
#include "Logger.h"

int holdWaterSolver(const std::vector<int>& heights)
{
  int lmax, rmax, max, sum;
  const int *lptr, *rptr;
  if (heights.size() < 3)
    return 0;
  lptr = &heights.front();
  rptr = &heights.back();
  lmax = *lptr;
  rmax = *rptr;
  sum = 0;
  // Why stop for rptr++?
  while (lptr != rptr) {
    max = MIN(lmax, rmax);
    if (*lptr < *rptr) {
      lptr++;
      if (*lptr < max) {
        sum += max - *lptr;
        continue;
      }
      if (*lptr > lmax)
        lmax = *lptr;
    }
    else {
      rptr--;
      if (*rptr < max) {
        sum += max - *rptr;
        continue;
      }
      if (*rptr > rmax)
        rmax = *rptr;
    }
  }
  return sum;
}

MAIN()
{
  std::vector<int> heights = {0, 2, 1, 3, 1, 2, 0, 4, 2, 3, 1};
  Log("%d", holdWaterSolver(heights));
  return 0;
}
