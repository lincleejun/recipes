#ifndef ANTS_H_
#define ANTS_H_

#include <vector>

// nֻ������ÿ��1cm���ٶ��ڳ�ΪLcm�ĸ��������С����������յ�����������ֻ��������ʱ��
// ֻ�ܵ�ͷ����ȥ������ÿһֻ����i����������������˵ľ���x[i]���������ǲ�֪������
// �ĳ�ʼ���򡣼��㣬�������ϵ�����Ҫ�����ʱ����ʱ�䡣

namespace alg {

std::pair<int, int> Ants(int stick_length, const std::vector<int>& ants);

}  // namespace alg

#endif  // ANTS_H_
