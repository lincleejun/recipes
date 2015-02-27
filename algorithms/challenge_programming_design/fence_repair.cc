// poj 3253

#include <vector>
#include <queue>
#include <xfunctional>

#include "gtest/gtest.h"

namespace alg {

int FenceRepair(std::vector<int> data) {
  int answer = 0;
  int count = data.size();
  while (count > 1) {
    int min1 = 0;
    int min2 = 1;
    if (data[min1] > data[min2]) {
      std::swap(min1, min2);
    }
    for (int i = 2; i < count; ++i) {
      if (data[i] < data[min1]) {
        min2 = min1;
        min1 = i;
      } else if (data[i] < data[min2]) {
        min2 = i;
      }
    }
    int t = data[min1] + data[min2];
    answer += t;
    if (min1 == count -1) {
      std::swap(min1, min2);
    }
    data[min1] = t;
    data[min2] = data[count - 1];
    --count;
  }

  return answer;
}

int FenceRepairUseQueue(std::vector<int> data) {
  std::priority_queue<int, std::vector<int>, std::greater<int> > datas;
  for (auto& item : data) {
    datas.push(item);
  }

  int answer = 0;
  while (datas.size() > 1) {
    int l1 = datas.top();
    datas.pop();
    int l2 = datas.top();
    datas.pop();
    answer += l1 + l2;
    datas.push(l1 + l2);
  }
  return answer;
}

}  // namespace alg

TEST(FenceRepair, FenceRepair) {
  std::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(33, alg::FenceRepair(v));

  std::vector<int> v1 = {5, 3, 4, 2, 1};
  EXPECT_EQ(33, alg::FenceRepair(v1));

  std::vector<int> v2 = {5, 4, 3, 2, 1};
  EXPECT_EQ(33, alg::FenceRepair(v2));

  std::vector<int> v3 = {8, 5, 8};
  EXPECT_EQ(34, alg::FenceRepair(v3));
}


TEST(FenceRepair, FenceRepairUseQueue) {
  std::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(33, alg::FenceRepairUseQueue(v));

  std::vector<int> v1 = {5, 3, 4, 2, 1};
  EXPECT_EQ(33, alg::FenceRepairUseQueue(v1));

  std::vector<int> v2 = {5, 4, 3, 2, 1};
  EXPECT_EQ(33, alg::FenceRepairUseQueue(v2));

  std::vector<int> v3 = {8, 5, 8};
  EXPECT_EQ(34, alg::FenceRepairUseQueue(v3));
}