/*
 *  BOJ 14427. 수열과 쿼리 15
 *
 *  시간복잡도 : O(MlogN)
 *
 *  이진트리를 구성하고 리프노드의 맨 왼쪽부터 N개의 입력 받은 값들을 순서대로 넣는다.
 *  리프 노드가 있는 레벨의 바로 위의 레벨의 모든 노드에서 자식들 중에 더 작은 값을 
 *  자신의 노드에 저장한다. 만약 자식의 값이 바뀐다면 바뀐 자식의 조상들만 큰 레벨에서
 *  높은 레벨로 가면서 자식들 중에 더 작은 값을 갱신시키면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 100002
typedef pair<int, int> pi;

pi tree[MXN * 4];
int N, M;
int pli;
const int INF = 2e9;

bool cmp(pi a, pi b) {
	if (a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}

void init() {
	cin >> N;
	pli = 1;
	while (pli < N) pli *= 2;
	pli--;
	int a;
	// 모든 리프 노드를 INF로 초기화
	for (int i = 1; i <= pli + 1; i++) tree[pli + i] = { INF, 0 };
	
	// 리프노드의 맨 왼쪽부터 {값, 인덱스}를 저장
	for (int i = 1; i <= N; i++) {
		cin >> a;
		tree[pli + i] = { a,i };
	}
	// 리프노드의 모든 부모부터 루트까지 자식들중에 더 작은 값을 저장 만약 값이 같다면 인덱스가 작은 거 저장 
	for (int i = pli; i >= 1; i--) {
		tree[i] = cmp(tree[i * 2], tree[i * 2 + 1]) ? tree[i * 2] : tree[i * 2 + 1];
	}
}

void update(int idx) {
	while (idx) {
		tree[idx] = cmp(tree[idx * 2], tree[idx * 2 + 1]) ? tree[idx * 2] : tree[idx * 2 + 1];
		idx /= 2;
	}
}

int main() {
	fastio();
	init();
	cin >> M;
	int q, a, b;
	for (int i = 0; i < M; i++) {
		cin >> q;
		// 해당 인덱스의 리프 노드에 바뀐 값 b를 넣어주고
		// 이 노드의 부모부터 루트까지 가면서 자식들 중 더 작은 값을 갱신
		if (q==1) {
			cin >> a >> b;
			tree[pli + a].first = b;
			update((pli + a) / 2);
		}
		// 항상 루트에는 가장 작은 값이 저장 루트의 인덱스를 출력하면 끝
		else cout << tree[1].second << '\n';
	}
	return 0;
}