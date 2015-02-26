#include "algorithms/challenge_programming_design/ants.h"

#include <algorithm>
#include <iostream>

#include "gtest/gtest.h"

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

TEST(Ants, ants) {
  int l = 10;
  std::vector<int> v = { 2, 6, 7 };
  auto result = alg::Ants(l, v);
  EXPECT_EQ(result.first, 4);
  EXPECT_EQ(result.second, 8);
}