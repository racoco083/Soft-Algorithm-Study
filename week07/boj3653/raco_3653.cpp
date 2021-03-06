/*
 *  BOJ 3653. 영화 수집
 *
 *  시간복잡도 : O(Mlog(N+M))
 *  
 *  인덱스     : 1 2 3 4 5
 *  영화 번호  : 5 4 3 2 1
 *  N이 5라고 한다면 위와 같이 초기값을 구성한다.
 *  각 영화 번호의 인덱스를 이용해 펜윅트리에 update한다.
 *  그리고 영화 번호 5의 인덱스는 1이라는 것을 chk[5] = 1로 한다.
 *  이렇게 모든 영화의 번호와 인덱스를 chk에 매칭한다.
 *  5번 영화를 골라보자 그러면 5번 영화의 위에는 4개의 영화가 있다.
 *  펜윅트리가 있으니 sum(5) - sum(1)을 하면 4가 나온다.
 *  그리고 5번 영화를 맨 위로 올려야 한다. 맨 오른쪽(인덱스 값이 제일 큰 것)이 제일 위에 있는 영화다
 *  인덱스     : 1 2 3 4 5 6
 *  영화 번호  : 0 4 3 2 1 5
 *  가 되므로 인덱스 1번에 영화를 지웠으니 이걸 포함하는 모든 비트의 펜윅트리에
 *  1씩 감소시킨다. 그리고 인덱스 6에 5번 영화가 갔으니 인덱스 6을 포함하는 모든 비트의
 *  펜윅트리에 1를 증가시킨다. chk[5] = 6으로 바꾸어 주는 것을 반복하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 100002

int N, M;
int tree[MXN * 2];
int chk[MXN * 2];

int sum(int idx) {
	int ret = 0;
	while (idx) {
		ret += tree[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

void update(int idx, int diff) {
	while (idx <= N + M) {
		tree[idx] += diff;
		idx += (idx & -idx);
	}
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	while (TC--) {
		cin >> N >> M;
		memset(tree, 0, sizeof(tree));
		memset(chk, 0, sizeof(chk));
		for (int i = 1; i <= N; i++) {
			update(i, 1);
			chk[N - i + 1] = i;
		}
		int in;
		for (int i = 1; i <= M; i++) {
			cin >> in;
			cout << sum(N + i - 1) - sum(chk[in]) << ' ';
			update(chk[in], -1);
			update(N + i, 1);
			chk[in] = N + i;
		}
		cout << '\n';
	}
	return 0;
}