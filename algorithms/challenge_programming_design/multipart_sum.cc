
#include <cassert>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

// ��N�ֲ�ͬ��С������ai��ÿ�ָ�mi�����ж��Ƿ���Դ���Щ����֮��ѡ������ʹ���ǵĺ�ǡ��ΪK
// DP����
// dp[i+1][j] = ��ǰi�����Ӻ͵õ�jʱ��i���������ʣ����ٸ�
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