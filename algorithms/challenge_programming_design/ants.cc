#include "algorithms/challenge_programming_design/ants.h"

#include <algorithm>
#include <iostream>

namespace alg {

std::pair<int, int> Ants(int stick_length, const std::vector<int>& ants) {
  int max = 0;
  int min = 0;
  for (const auto& i : ants) {
    min = std::max(min, std::min(i, stick_length - i));
    max = std::max(max, std::max(i, stick_length - i));
  }

  std::pair<int, int> result;
  result.first = min;
  result.second = max;
  return result;
}

}  // namespace alg


int main() {
  int l = 10;
  std::vector<int> v = {2, 6, 7};
  auto result = alg::Ants(l, v);
  std::cout << "min = " << result.first << std::endl;
  std::cout << "max = " << result.second << std::endl;

  return 0;
}