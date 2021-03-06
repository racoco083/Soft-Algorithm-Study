// 루트 정점인 1부터 시작해서 모든 정점 i를 순회하면서
// 해당 정점의 부모 정점을 p[i]배열에 담는다.
// p[2]부터 시작해서 값을 출력해주면 되는 문제이다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 100001

int N;
vector<int> adj[MAX];
int p[MAX];// parent

void bfs(int s) {
	queue<int> qu;
	qu.push(s);
	p[s] = 1;
	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();
		for (int i = 0; i < adj[cur].size(); i++) {
			int n = adj[cur][i];
			if (p[n] == 0) {
				p[n] = cur;
				qu.push(n);
			}
		}
	}
}

int main() {
	fastio();
	cin >> N;
	int a, b;
	for (int i = 1; i < N; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	bfs(1);
	for (int i = 2; i <= N; i++) {
		cout << p[i] << '\n';
	}
	return 0;
}