/*
 *  BOJ 1275. 커피숍2
 *
 *  시간복잡도 : O(QlogN)
 *
 *  구간 합 구하기 문제랑 동치다. 구간 합 구하기 문제 설명을 보면 된다.
 *  [a,b]구간의 합을 구 할 때 여기선 a가 b보다 더 클 수 있다. 
 *  그래서 한 번 틀렸다. 그것만 신경써주면 된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 100001
typedef long long ll;

int N, Q;
ll tree[MXN * 4];
int pli;// parent_last_index 부모 노드 중에 가장 인덱스가 큰 값을 저장한다.

void init() {
	pli = 1;// root는 1부터 시작한다.
	while (pli < N) pli *= 2;
	pli--;
	// 왼쪽 노드부터 오른쪽으로 차례대로 값을 입력받는다.
	for (int i = 1; i <= N; i++) cin >> tree[pli + i];
	// 위에서 얻은 단말 노드 정보를 통해 부모의 값을 갱신시킨다.
	for (int i = pli; i >= 1; i--) tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll sum(int s, int e) {
	ll ret = 0;
	s += pli;
	e += pli;
	while (s <= e) {
		if (s % 2 == 1) ret += tree[s];
		if (e % 2 == 0) ret += tree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}

void update(int idx, ll chg) {// 바꿔야 할 순서의 인덱스 index, 바꿀 숫자 change
	idx += pli;
	ll diff = chg - tree[idx];
	while (idx) {
		tree[idx] += diff;
		idx /= 2;
	}
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int main() {
	fastio();
	cin >> N >> Q;
	init();

	ll a, b, c, d;
	for (int i = 0; i < Q; i++) {
		cin >> a >> b >> c >> d;
		// a가 b보다 클 때도 신경써주어야 한다.
		if (a > b) swap(a, b);
		cout << sum(a, b) << '\n';
		update(c, d);
	}
	return 0;
}