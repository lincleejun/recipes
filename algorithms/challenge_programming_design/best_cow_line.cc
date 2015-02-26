//FJ is about to take his N(1 ¡Ü N ¡Ü 2, 000) cows to the annual"Farmer
// of the Year" competition.In this contest every farmer arranges his
// cows in a line and herds them past the judges.
//The contest organizers adopted a new registration scheme this year:
// simply register the initial letter of every cow in the order they
// will appear(i.e., If FJ takes Bessie, Sylvia, and Dora in that order
// he just registers BSD).After the registration phase ends,
// every group is judged in increasing lexicographic order according
// to the string of the initials of the cows' names.
//FJ is very busy this year and has to hurry back to his farm, 
// so he wants to be judged as early as possible.He decides to rearrange
// his cows, who have already lined up, before registering them.
//FJ marks a location for a new line of the competing cows.He then 
// proceeds to marshal the cows from the old line to the new one by 
// repeatedly sending either the first or last cow in the(remainder 
// of the) original line to the end of the new line.When he's finished, 
// FJ takes his cows for registration in this new order.
//Given the initial order of his cows, determine the least
// lexicographic string of initials he can make this way.

#include <string>
#include "gtest/gtest.h"

namespace alg {

std::string BestCowLine(const std::string& str) {
  int start = 0;
  int end = str.length() - 1;
  bool use_left = false;
  int insert_index = 0;
  std::string result;
  result.resize(str.length());

  while (start <= end) {
    use_left = false;
    for (int i = 0; start + i <= end; ++i) {
      if (str[start + i] < str[end - i]) {
        use_left = true;
        break;
      } else if (str[start + i] > str[end - i]) {
        use_left = false;
        break;
      }
    }

    result[insert_index++] = use_left ? str[start++] : str[end--];
  }

  return result;
}

}  // namespace alg

TEST(BestCowLine, BestCowLine) {
  EXPECT_EQ("ABCBCD", alg::BestCowLine("ACDBCB"));
  EXPECT_EQ("ABCD", alg::BestCowLine("ABCD"));
  EXPECT_EQ("ABCD", alg::BestCowLine("DCBA"));
}