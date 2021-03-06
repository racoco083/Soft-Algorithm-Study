/*
 *  BOJ 2618. 경찰자
 *
 *  시간복잡도 : O(N^2)
 * 
 *  cache[i][j] : 첫 번째 경찰차의 위치 i와 두 번째 경찰차의 위치 j에 있을 때
 *  남은 사건 처리했을 때 최소비용
 *
 *  사건은 1~w까지 순서대로 처리하므로 i번째 사건이 일어난 곳의 좌표를 i로
 *  표현가능하다. 첫 번째 경찰차 좌표의 인덱스를 a, 두 번째 경찰차 좌표의
 *  인덱스를 b, 처리해야 할 사건의 좌표 인덱스를 k라고 할 때 a가 k를 처리했을 때
 *  비용과 b가 k를 처리했을 때 비용 중에 더 작은 값을 담아 재귀적으로 리턴한다.
 *  이렇게 처리하면 최소비용을 구하고, 각 사건을 처리할 때 어떤 경찰차가 사건을
 *  해결하였는지는 구한 cache값을 이용해 (cache[k][b] + taxi(a, k)) == cache[a][b]
 *  같다는 말은 a에서 k사건을 처리했을 때 비용 + 첫 번째 경찰차의 인덱스가 k이고,
 *  두 번째 경찰차의 인덱스가 b일 때 나머지 사건 처리했을 때 최소비용이랑 같다는 것은
 *  첫 번째 경찰차가 k사건을 처리해야 한다는 것이고 아니면 두 번째 경찰차가 k사건을
 *  처리하는 것이 최소비용이 나온다는 소리이다.
 *  
 */
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 1005

class Pos {
public:
	int y, x;
	Pos() {}
	Pos(int _y, int _x) : y(_y), x(_x) {}
};

int N, W;
Pos w[MXN];
int cache[MXN][MXN];
const int INF = 2e9;

int abs(int a) {
	return (a < 0) ? -a : a;
}

int taxi(int p1, int p2) {
	return abs(w[p1].y - w[p2].y) + abs(w[p1].x - w[p2].x);
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int solve(int a, int b, int k) {
	if (k > W + 1) return 0;

	int &ret = cache[a][b];
	if (ret != 0) return ret;
	ret = INF;

	return ret = min(solve(k, b, k+1) + taxi(a, k), solve(a, k, k+1) + taxi(b, k));
}

void tracking(int a, int b, int k) {
	if (k > W + 1) return;

	if ((cache[k][b] + taxi(a, k)) == cache[a][b]) {
		cout << 1 << '\n';
		tracking(k, b, k + 1);
	}
	else {
		cout << 2 << '\n';
		tracking(a, k, k + 1);
	}
}

int main() {
	cin >> N >> W;
	Pos p;
	w[0] = Pos(1, 1);
	w[1] = Pos(N, N);
	for (int i = 2; i <= W+1; i++) {
		cin >> w[i].y >> w[i].x;
	}
	cout << solve(0, 1, 2) << '\n';
	tracking(0, 1, 2);
	return 0;
}