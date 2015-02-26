#ifndef ANTS_H_
#define ANTS_H_

#include <vector>

// n只蚂蚁以每秒1cm的速度在长为Lcm的竿子上爬行。蚂蚁爬到终点会掉下来。两只蚂蚁相遇时，
// 只能调头爬回去。对于每一只蚂蚁i，给定其距离竿子左端的距离x[i]，但是我们不知道蚂蚁
// 的初始朝向。计算，所有蚂蚁掉落需要的最短时间和最长时间。

namespace alg {

std::pair<int, int> Ants(int stick_length, const std::vector<int>& ants);

}  // namespace alg

#endif  // ANTS_H_
