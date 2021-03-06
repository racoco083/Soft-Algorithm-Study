/*
 *  BOJ 2018. 수들의 합 5
 *  
 *  > 투포인터
 *  시간 복잡도 : O(N)
 *  공간 복잡도 : O(1)
 * 
 *  > 연속된 자연수들의 합
 *  시간 복잡도 : O(sqrt N)
 *  공간 복잡도 : O(1)
 * 
 *  이 문제를 투포인터와 그냥 연속된 자연수의 합의 성질로 풀어봤습니다.
 *  먼저 투포인터는 왼쪽(포함)과 오른쪽(미포함) 포인터를 가지고서 그 구간의 합을 
 *  계속 구해갑니다. 이때, 이 합이 n과 같다면 카운터를 올려주고, 
 *  합이 크다면 왼쪽 포인터를 한 칸 움직이고, 작다면 오른쪽 포인터를 한 칸 움직입니다.
 * 
 *  연속된 자연수의 합의 성질은 사용된 수의 갯수를 k라고 하고, 그때의 처음 수를 a라고 하면 
 *  k * (2 * a + k - 1) / 2 = n 의 관계를 갖습니다. 이때, 2를 이항시키면, 
 *  k * (2 * a + k - 1) = 2 * n이고, 왼쪽의 곱셈에서 모든 수들은 자연수이므로 
 *  k는 2 * n의 약수임을 알 수 있습니다. 그래서 2 * n의 약수만 확인하면 됩니다. 
 *  그럼 이 식을 a에 대하여 정리하면 a = (2 * n / k - k + 1) / 2 입니다. 
 *  이 상태에서 a는 자연수가 나와야 하고, k * k < 2 * n인 경우만 확인해야 합니다. 
 *  왜냐하면, k * k >= 2 * n인 경우는 k >= 2 * n / k 이므로 a <= 0이 됩니다.
 *  이건 자연수라는 조건을 위반하므로 k * k < 2 * n인 경우만 확인해서 a가 자연수가 되는 
 *  상황일 때만 카운터를 올려주면 됩니다. 
 */

#include <cstdio>
using namespace std;

// 투포인터
// int main(int argc, char *argv[]) {
//   int n, l = 1, r = 2, s = 1, cnt = 1;
//   scanf("%d", &n);
//   while (l < r && r <= n) {
//     if (s == n) ++cnt, s -= l++;
//     else if (s < n) s += r++;
//     else s -= l++;
//   }
//   return !printf("%d\n", cnt);
// }

// 연속된 자연수의 합의 성질 
int main(int argc, char *argv[]) {
  int n, i, cnt = 0;
  scanf("%d", &n);
  n *= 2; // 2 * N으로 만들어 줍니다.
  for (i = 1; i * i < n; ++i) { // i * i < 2 * N인 경우만 확인합니다.
    if (n % i == 0 && (n / i - i + 1) % 2 == 0)  // 2 * N의 약수이면서, a가 자연수가 되는 상황만 카운트해줍니다.
      ++cnt;
  }
  return !printf("%d\n", cnt);
}