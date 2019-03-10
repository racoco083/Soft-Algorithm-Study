/*
 *  BOJ 1948. 임계경로
 *
 *  시간복잡도 : O(M)
 *  
 *  시작점에서 도착점으로 가면서 dist값을 갱신하고
 *  도착점에서 시작점으로 가면서 rdist값을 갱신해
 *  도착지점에서 출발 할 때 nextCost + dist[next] == dist[E]
 *  같으면 도로 카운트를 센다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MXN 10002
typedef pair<int, int> pi;

int indegree[MXN + 1];
int rindegree[MXN + 1];
vector<pi> adj[MXN + 1];
vector<pi> edge[MXN + 1];
int N, M, S, E;
int dist[MXN + 1];
int rdist[MXN + 1];

int max(int a, int b) {
	return a > b ? a : b;
}

// 위상정렬을 통해 시작 정점으로 부터 현 정점까지 가장 가중치가 높은 값을
// dist[현재 정점]에 저장한다.
void bfs() {
	queue<pi> qu;
	dist[S] = 1;
	qu.push({ 1, S });
	while (!qu.empty()) {
		int cur = qu.front().second;
		int cost = qu.front().first;
		qu.pop();

		for (int i = 0; i < adj[cur].size(); i++) {
			int next = adj[cur][i].second;
			int nextCost = cost + adj[cur][i].first;

			if (dist[next] < nextCost) {
				dist[next] = nextCost;
			}

			indegree[next]--;
			if (!indegree[next]) {
				qu.push({ dist[next], next });
			}
		}
	}
}

// 구한 dist값을 이용해 끝 지점부터 시작해서 
// 도착 지점에서 출발해서 시작지점으로 가는 것 역시 위상 정렬을 이용해
// 안 풀면 시간초과 난다. 위상정렬을 하면 간선을 지워가면서 처리하니
// 간선의 개수가 시간복잡도가 된다. 
// 모든 정점이 qu에 한 번씩만 들어가는 것을 알 수 있다.
// 하지만 그냥 bfs를 하면 방문 했던 정점을 여러 번 방문하니 시간 초과가 난다.

int calc_cnt() {
	int ret = 0;
	queue<pi> qu;
	qu.push({ 0, E });
	rdist[E] = 0;
	while (!qu.empty()) {
		int cur = qu.front().second;
		int cost = qu.front().first;
		qu.pop();

		for (int i = 0; i < edge[cur].size(); i++) {
			int next = edge[cur][i].second;
			int nextCost = cost + edge[cur][i].first;
			
			if (nextCost + dist[next] == dist[E]) {
				ret++;
			}

			if (rdist[next] < nextCost) {
				rdist[next] = nextCost;
			}

			rindegree[next]--;
			if (!rindegree[next]) {
				qu.push({ rdist[next], next });
			}
		}
	}
	return ret;
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b, w;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> w;
		adj[a].push_back({ w, b });
		edge[b].push_back({ w, a });
		indegree[b]++;
		rindegree[a]++;
	}
	cin >> S >> E;
	bfs();
	cout << dist[E] - 1 << '\n';
	cout << calc_cnt() << '\n';
	return 0;
}