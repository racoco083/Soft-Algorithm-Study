/*
 *  BOJ 1280. 나무 심기
 *
 *  시간복잡도 : O(Nlog(2*10^5))
 *
 *  N개의 값이 들어 올때마다 이 값 in을 펜윅의 비트로 하여 in의 합에 대한 펜윅
 *  tree_sum과 in의 개수에 대한 펜윅tree_cnt를 구한다. in에 입력을 받을 때마다
 *  (in보다 큰 값들의 합) - in * (in보다 큰 값들의 개수) => in보다 큰 값들과 in의 차이
 *  in * (in보다 작은 값들의 개수) - (in보다 작은 값들의 합) => in보다 작은 값들과 in의 차이
 *  위의 과정을 반복해서 구해주면서 곱해주면 된다.
 *  어디가 틀린지 못 찾고 있었는데 모카님이 찾아주셔서 해결할 수 있었다.
 * 
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MOD 1000000007
#define MXN 200002
typedef long long ll;
int N;
ll ans;

ll tree_cnt[MXN+1];// 개수를 구하기 위한 펜윅트리
ll tree_sum[MXN+1];// 합을 구하기 위한 펜윅트리

void update(ll tree[], int idx, ll diff) {
	while (idx <= MXN) { // N으로 해서 틀렸다.
		tree[idx] += diff;
		idx += (idx & -idx);
	}
}

ll sum(ll tree[], int idx) {
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
	ll in;
	ans = 1;
	for (int i = 1; i <= N; i++) {
		cin >> in;
		// 0 부터이니 펜윅의 인덱스이므로 0은 될 수 없다. 모든 값을 1증가시킨다. 모든 값을 1씩 증가시켜도
		// 차이는 똑같기 때문이다.
		in++;
		if (i == 1) {
			update(tree_sum, in, in);
			update(tree_cnt, in, 1);
			continue;
		}
		// MXN의 인덱스에 도달할 수 있으니 tree의 인덱스 범위를 MXN+1로 해주어야 하는데 MXN으로 하여 MXN에 도달하면
		// 오류가 난다. 주의하자!
		// in이 곧 펜윅의 인덱스이다. in보다 큰 값들의 합 - in보다 큰 값들의 개수*in을 하면 in보다 큰 값들의 모든 차이를 구한다.
		// 그리고 같은 좌표에 나무를 심을 수도 있지만 같은 값인 in은 포함하지 않아도 된다. 어차피 in-in의 차이는 0이기 때문이다. 
		ll cur = (sum(tree_sum, MXN) - sum(tree_sum, in) - in * (sum(tree_cnt, MXN) - sum(tree_cnt, in))) % MOD;
		// MOD로 나누어 주어야 하는데 cur = (cur+x)를 해주어야 하는데 cur += x를 해주어 틀렸다. 주의하자!
		// in보다 작은 값의 개수*in - in보다 작은 값들의 합을 cur에 더해준다.
		cur = (cur + (in * (sum(tree_cnt, in - 1)) - sum(tree_sum, in - 1))) % MOD;
		ans = (ans * cur) % MOD;
		update(tree_sum, in, in);
		update(tree_cnt, in, 1);
	}
	cout << ans << '\n';
	return 0;
}
