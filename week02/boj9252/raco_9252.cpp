// 문자열 A : 첫 번째 입력 받은 문자열
// 문자열 B : 두 번째 입력 받은 문자열
// dp[i][j] : 문자열A의 i인덱스 까지 문자열을 사용했을때, 
// 문자열B의 j번째 인덱스 까지의 문자열을 사용했을 때의 최대 길의의 문자열 
// 2차원 스트링 dp를 이용해서 문자열을 서로 비교한다.
// 문자열 A[i]와 B[i]의 문자열이 같다면 dp[i][j]에 dp[i-1][j-1]+A[i]를 넣는다.
// 이 값은 dp[i][j-1], dp[i-1][j]의 길이 보다 크거나 같기 때문이다.
// 만약 A[i]와 B[i]가 다르다면 그 때는 dp[i][j-1], dp[i-1][j]중에
// 길이가 더 긴 문자열 아무거나 dp[i][j]에 갱신시킨다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string>
using namespace std;
#define MXN 1001

string dp[MXN][MXN];
string A, B;

void solve() {
	for (int i = 1; i <= A.size(); i++) {
		for (int j = 1; j <= B.size(); j++) {
			if (A[i - 1] == B[j - 1]) dp[i][j] = dp[i - 1][j - 1] + A[i - 1];
			else dp[i][j] = (dp[i - 1][j].size() > dp[i][j - 1].size()) ? dp[i - 1][j] : dp[i][j - 1];
		}
	}
}

int main() {
	fastio();
	cin >> A >> B;
	solve();
	cout << dp[A.size()][B.size()].size() << '\n' << dp[A.size()][B.size()] << '\n';
	return 0;
}