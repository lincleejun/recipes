
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace alg {

int Expedition(int L, int P,
  const std::vector<int>& a,
  const std::vector<int>& b) {
  std::priority_queue<int> gas;
  int answer = 0;
  int pos = 0;
  int tank = P;
  for (unsigned int i = 0; i < a.size(); ++i) {
    int d = a[i] - pos;
    while (tank - d < 0) {
      if (gas.empty()) {
        return -1;
      }
      tank += gas.top();
      gas.pop();
      ++answer;
    }
    tank -= d;
    pos = a[i];
    gas.push(b[i]);
  }
  return answer;
}


}  // namespace alg

TEST(Expedition, Expedition) {
  int l = 25;
  int p = 10;
  std::vector<int> a = {10, 14, 20, 21};
  std::vector<int> b = {10, 5, 2, 4};
  EXPECT_EQ(2, alg::Expedition(l, p, a, b));
}