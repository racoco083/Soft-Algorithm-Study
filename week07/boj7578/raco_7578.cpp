/*
 *  BOJ 7578. 공장
 *
 *  시간복잡도 : O(NlogN)
 *
 *  B를 왼쪽에서부터 처리해 나가며 B와 같은 값의 A를 연결한다.
 *  이렇게 연결하며 처리된 A의 원소 인덱스 값을 펜윅의 인덱스로 하여
 *  1씩 증가시킨다. 그리고 sum을 통해 현재 매칭된 A의 원소중에 현재 인덱스의 
 *  A가 왼쪽에서 몇 번째인지 파악한 ret를 구한 후 총 연결된 A의 원소는 i개 이므로
 *  i-ret를 하면 곧 현재 교차된 케이블 쌍의 개수를 구하게 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 500002
typedef long long ll;

ll num[MXN * 2];// 기계의 식별번호는 10^6이하로서 인덱스는 A의 원소 값이 된다.
ll bcai[MXN + 1];// B_connect to A, then A_index
ll tree[MXN + 1];// B와 매칭되는 A값을 기준으로 펜윅을 구성한다.
int N;

void update(int idx, ll diff) {
	while (idx <= N) {
		tree[idx] += diff;
		idx += (idx & -idx);
	}
}

ll sum(int idx) {
	ll ret = 0;
	while (idx) {
		ret += tree[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

int main() {
	fastio();
	cin >> N;
	int in;
	for (int i = 1; i <= N; i++) {
		cin >> in;
		// in이 129이면 num[129] = i가 된다.
		num[in] = i;
	}
	for (int i = 1; i <= N; i++) {
		cin >> in;
		// i는 B의 현재 인덱스이고 num[in]은 A의 원소가 in일 때 이 원소의 순서이다.
		// B와 A의 같은 값의 원소 매칭시킨다.
		bcai[i] = num[in];
	}
	ll ans = 0;
	// update 시켜나가면서 교차하는 케이블 쌍의 개수를 구한다.
	// B를 왼쪽 원소부터 순서대로 처리해 나가면서 이때의 B의 원소와 매칭된
	// A의 원소의 인덱스를 펜윅의 인덱스로 하여 update한다. B의 원소는
	// 항상 맨 오른쪽에 있으니 A와 매칭될 때 현재의 A도 매칭된 A중에
	// 가장 오른쪽에 있으면 교차 케이블은 0개이다. i는 B의 인덱스를
	// ret는 현재 매칭된 A의 원소중에 현재 인덱스의 A가 왼쪽에서 몇 번째인지를
	// 나타낸다. 1이면 자기자신의 값을 가장 오른쪽에 있는 것으로 교차된 것이 없다는 뜻이고
	// 그래서 B의 인덱스인 i에 -ret를 하면 현재 인덱스의 교차한 케이블 쌍의 개수를 구할 수 있다.
	for (int i = 1; i <= N; i++) {
		update(bcai[i], 1);
		ll ret = sum(bcai[i]);
		ans += (i - ret);
	}
	cout << ans << '\n';
	return 0;
}