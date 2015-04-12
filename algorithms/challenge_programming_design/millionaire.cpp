/*
You have been invited to the popular TV show "Would you like to be a millionaire?". Of course you would!

The rules of the show are simple:
Before the game starts, the host spins a wheel of fortune to determine P, the probability of winning each bet.
You start out with some money: X dollars.
There are M rounds of betting. In each round, you can bet any part of your current money, including none of it or all of it. The amount is not limited to whole dollars or whole cents.
If you win the bet, your total amount of money increases by the amount you bet. Otherwise, your amount of money decreases by the amount you bet.

After all the rounds of betting are done, you get to keep your winnings (this time the amount is rounded down to whole dollars) only if you have accumulated $1000000 or more. Otherwise you get nothing.
Given M, P and X, determine your probability of winning at least $1000000 if you play optimally (i.e. you play so that you maximize your chances of becoming a millionaire).

Input

The first line of input gives the number of cases, N.

Each of the following N lines has the format "M P X", where:

M is an integer, the number of rounds of betting.
P is a real number, the probability of winning each round.
X is an integer, the starting number of dollars.
Output

For each test case, output one line containing "Case #X: Y", where:

X is the test case number, beginning at 1.
Y is the probability of becoming a millionaire, between 0 and 1.
Answers with a relative or absolute error of at most 10-6 will be considered correct.

Limits

1 ¡Ü N ¡Ü 100
0 ¡Ü P ¡Ü 1.0, there will be at most 6 digits after the decimal point.
1 ¡Ü X ¡Ü 1000000

Small dataset

1 ¡Ü M ¡Ü 5

Large dataset

1 ¡Ü M ¡Ü 15

Sample


Input

Output
2
1 0.5 500000
3 0.75 600000

Case #1: 0.500000
Case #2: 0.843750


*/

#include <iostream>
#include "gtest/gtest.h"


namespace alg {

const int MAX = 1000000;
double d[16][(1 << 15) + 1];

double Millionaire(int m, double p, double x) {
  if (x >= MAX)
    return 1.0;
  if (x < 1.0 / (1 << m))
    return 0.0;

  d[0][1] = 1.0;
  for (int j = 1; j <= m; j++) {
    d[j][1 << j] = 1.0;
    for (int i = 1; i < (1 << j); i++) {
      double c = 0.0;
      for (int k = (i + 1) / 2; k <= (1 << (j - 1)); k++) {
        if (i - k >= 0) {
          double t = p*d[j - 1][k] + (1 - p)*d[j - 1][i - k];
          if (t > c) c = t;
        }
      }
      d[j][i] = c;
    }
  }

  return d[m][(int)((1 << m)*(x / MAX))];
}

double Millionaire2(int m, int x, double p) {
  double dp[2][(1 << 15) + 1];
  int n = 1 << m;
  double* prev = dp[0];
  double* next = dp[1];
  memset(prev, 0, sizeof(double)* (n + 1));
  prev[n] = 1.0;
  for (int r = 0; r < m; ++r) {
    for (int i = 0; i <= n; ++i) {
      int jub = std::min(i, n - i);
      double t = 0.0;
      for (int j = 0; j <= jub; ++j) {
        t = std::max(t, p * prev[i + j] + (1 - p) * prev[i - j]);
      }
      next[i] = t;
    }
    std::swap(prev, next);
  }
  int i = x * n / MAX;
  return prev[i];
}

}  // namespace alg


TEST(Millionaire, millionaire) {
  EXPECT_EQ(0.5, alg::Millionaire(1, 0.5, 500000));
  EXPECT_EQ(0.843750, alg::Millionaire(3, 0.75, 600000));
}

TEST(Millionaire, millionaire2) {
  EXPECT_EQ(0.5, alg::Millionaire2(1, 500000, 0.5));
  EXPECT_EQ(0.843750, alg::Millionaire2(3, 600000, 0.75));
}

