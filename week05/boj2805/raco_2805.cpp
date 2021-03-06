/*
 *  BOJ 2805. 나무 자르기
 * 
 *  시간복잡도 O(log(1e9) * logN + NlogN)
 *  공간복잡도 O(N)
 *  
 *  입력 받은 나무 높이 값을 오름차순 정렬한 tree배열을 만들고
 *  이 값에 대한 누적합 배열 sa를 만들었습니다. 
 *  절단 높이를 0~10억 사이로 이분탐색을 합니다. 이분탐색을 하며 
 *  구한 mid값을 절단 높이로 설정하여 모든 나무를 자른 길이 합을
 *  구합니다. 이 값이 M보다 크면 ans값과 mid값을 비교하여 더 큰 값을
 *  ans에 대입합니다. 이분탐색이 종료할 때 까지 이 과정을 반복합니다.
 *
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 1000003

typedef long long ll;

int N, M;
ll tree[MXN];
ll sa[MXN];// sum_arr
const int INF = 2e13;

ll max(ll a, ll b) {
	return a > b ? a : b;
}

ll ub(int s, int e, ll v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (tree[m] <= v) {
			s = m + 1;
		}
		else e = m;
	}
	return e;
}

ll bs(ll s, ll e) {
	ll ans = 0;
	while (s <= e) {
		ll m = (e + s) / 2;
		// 설정된 절단 높이 m과 제일 차이가 없으면서 큰 값의 인덱스를
		// tree 배열에서 찾습니다.
		ll ui = ub(1, N + 1, m);
		// ui부터 N까지 모든 나무에 m값을 빼는 것을 O(1)에 구하기 위해
		// 차이를 구합니다.
		ll diff = N + 1 - ui;
		// 누적합 배열 sa를 이용해 ui부터 N까지 인덱스의 모든 나무길이 합을 구한 뒤
		// 절단 높이 * diff를 빼주어 가져갈 수 있는 나무 길이 합을 구합니다.
		// 누적합 배열을 이용해 O(1)만에 구할 수 있습니다.
		ll gw = sa[N] - sa[ui - 1] - (m*diff);// get wood
	    // 가져간 나무 길이 합이 M보다 크면 ans값과 m값을 비교해 더 큰 값을 ans에 갱신합니다.
		if (gw >= M) {
			ans = max(m, ans);
			s = m + 1;
		}
		else e = m - 1;
	}
	return ans;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> tree[i];
	tree[N + 1] = INF;
	sort(tree + 1, tree + 1 + N);
	for (int i = 1; i <= N; i++) {
		sa[i] = sa[i - 1] + tree[i];
	}

	cout << bs(0, 1000000000) << '\n';
	return 0;
}