// 3번 조건 '우수 마을'로 선정되지 못한 마을은 적어도 하나의 '우수 마을'과는 
// 인접해 있어야 한다.는 신경쓰지 않아도 된다. 이 문제는 우수마을 주민 합의
// 최대값을 찾는 문제이다. 우수마을로 선정되지 못한 마을이 우수마을과 
// 인접 해야지만 답을 찾을 수 있기 때문이다. 우수마을과 인접하지 않은 마을
// 주민들의 수를 더해 부모노드에 전달해도 dfs에서 max에 의해 걸러진다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MAX 10001

template<typename T>
class vector {
public:
	int ca, sz;
	T *arr;
	vector<T>() {
		sz = 0;
		ca = 16;
		arr = new T[ca];
	}
	void push_back(T a) {
		if (sz == ca) {
			ca *= 2;
			T* tmp = new T[ca];
			for (int i = 0; i < sz; i++) tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
		}
		arr[sz++] = a;
	}
	int size() { return sz; }
	T &operator[](int idx) { return arr[idx]; }
};

int N;
int arr[MAX];
vector<int> adj[MAX];
bool visited[MAX];

int max(int a, int b) {
	return a > b ? a : b;
}

// 현재 마을이 우수마을이면 다음 마을은 우수 마을로 지정하지 말고,
// 현재 마을이 우수마을이면 다음 마을은 우수 마을이 되는 것과 우수 마을이 되지 않는 것 중
// 더 큰 값을 return 받으면 된다.
int dfs(int v, bool f) { //vertex, flag(현재 마을이 우수마을이면 true 아니면 false)
	visited[v] = true;
	int ret = 0;
	for (int i = 0; i < adj[v].size(); i++) {
		int n = adj[v][i];
		if (visited[n]) continue;
		if (f) ret += dfs(n, false);
		else ret += max(dfs(n, false), dfs(n, true) + arr[n]);
	}
	visited[v] = false;
	return ret;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	int a, b;
	for (int i = 1; i < N; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int ans = max(dfs(1, false), dfs(1, true) + arr[1]);
	cout << ans << '\n';
	return 0;
}