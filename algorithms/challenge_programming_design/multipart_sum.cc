
#include <cassert>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

// 有N种不同大小的数字ai，每种各mi个，判断是否可以从这些数字之重选出若干使他们的和恰好为K
// DP问题
// dp[i+1][j] = 用前i种数加和得到j时第i种数最多能剩余多少个
namespace alg {

bool CanSumToK(const std::vector<int>& a,
               const std::vector<int>& m, int K) {
  assert(a.size() == m.size());
  int* dp = new int[K + 1];
  dp[0] = 0;
  for (unsigned int i = 0; i < a.size(); ++i) {
    for (int j = 0; j <= K; ++j) {
      if (dp[j] >= 0) {
        dp[j] = m[i];
      } else if (j < a[i] || dp[j - a[i]] <= 0) {
        dp[j] = -1;
      } else {
        dp[j] = dp[j - a[i]] - 1;
      }
    }
  }

  bool result = dp[K] >= 0;
  delete[] dp;
  return result;
}

}  // namespace alg


TEST(MultipartSum, multipartSum) {
  std::vector<int> a = {3, 5, 8};
  std::vector<int> m = {3, 2, 2};

  EXPECT_TRUE(alg::CanSumToK(a, m, 17));
}