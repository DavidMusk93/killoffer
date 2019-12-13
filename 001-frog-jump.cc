#include <vector>
#include "macro.h"
#include "Logger.h"

int frogJumpSolver(int total, const std::vector<int>& steps)
{
  int count = 0;
  if (total < 0)
    return 0;
  else if (total == 0)
    return 1;
  else
    for (auto i: steps)
      count += frogJumpSolver(total - i, steps);
  return count;
}

MAIN()
{
  std::vector<int> steps = {1, 2};
  Log("20, {1, 2}:%d", frogJumpSolver(20, steps));
  return 0;
}
