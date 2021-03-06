/*
 *  BOJ 3090. 차이를 최소로
 *
 *  시간복잡도 : O(NlogN * log(1e9))
 * 
 *  입력받은 값들을 pq(minheap)에 넣어줍니다. 이분 탐색의 m값은
 *  인접한 수들의 차이의 최대값으로 설정합니다. T의 연산만큼 배열의 
 *  값들을 1씩 감소시킬 수 있습니다. 감소만 시킬 수 있으므로 가장 작은
 *  값은 감소시킬 일이 없습니다. 이 값을 기준으로 하여 양 옆의 값들이 
 *  현재 값과 m보다 차이가 크다면 값을 현재값+m으로 바꾸어주고 그 차이를 
 *  카운트합니다. 현재 값과 양 옆은 m차이 이하로 맞추었으므로 현재 값은
 *  더 이상 볼 필요가 없고, 양 옆값들은 또 이 값들의 양 옆값과 m차이
 *  이하가 되도록 맞추어 주어야 하므로 pq에 넣어줍니다. 그래서 pq에는
 *  원소가 최대 2*N개 들어갈 수 있습니다.
 *  
 *  예제 4 2 3 7 6, m==1 일때를 예로 minheap과 배열의 변화를 보자
 *  minheap의 원소는 (arr[i], i)이다.
 *  인덱스는 one base이다.
 *  초기 pq와 배열 상태
 *            (2, 2)
 *      (4, 1)      (3, 3)
 *  (7, 4) (6, 5)
 *  => 4 2 3 7 6
 *
 *  인덱스 2의 2값을 기준으로 하여 양 옆값을 차이 m이하로 맞춘다.
 *  그러면 4는 3이 되고 (3, 1)이 pq에 들어간다.
 *            (3, 3)
 *      (4, 1)      (3, 1)
 *  (7, 4) (6, 5)
 *  => 3 2 3 7 6
 *  
 *  인덱스 3의 3값을 기준으로 하여 양 옆값을 차이 m이하로 맞춘다.
 *  양 옆 값이 3보다 작다는 것은 이전에 기준이 되어 현재 3을 감소시켜서
 *  차이가 m이하가 되도록 맞췄다는 뜻으로 더 작은 값은 보지 않아도 되고
 *  3의 양 옆값 중 3보다 큰 값 중 차이가 m보다 큰 것만 신경써주면 된다.
 *  그럼 인덱스 4의 7값만 4로 바꾸어 주고 (4, 4)값을 pq에 넣어 나중에 이값이
 *  기준이 되어 양 옆값을 줄일 수 있도록 한다.
 *            (3, 1)
 *      (4, 1)      (4, 4)
 *  (7, 4) (6, 5)
 *  => 3 2 3 4 6
 *  
 *  인덱스 1의 값은 더 이상 4가 아니고 3이 이 뜻은 양 옆의 더 작은 값에 의해
 *  4값이 감소가 되어 3이 되었고 더 작아진 값이니 pq에 나중에 들어왔지만
 *  먼저 pq에서 나오게 되어 기준값이 되어 양 옆 값들을 벌써 차이가 m이하로
 *  맞추어 주었다는 소리이다. 그러면 볼 값은 인덱스 2뿐인데 이 값은
 *  3+m==4이거나 3과 같거나 더 작을 수 밖에 없다. 4입장에서는 자신보다m더 큰
 *  값만 신경쓰므로 인덱스 2값은 무시된다.
 *            (4, 1)
 *      (6, 5)      (4, 4)
 *  (7, 4)
 *  => 3 2 3 4 6
 *
 *  배열에는 아무일도 일어나지 않는다.
 *            (4, 4)
 *      (6, 5)     
 *  (7, 4)
 *  => 3 2 3 4 6
 *
 *  인덱스 4의 4값을 기준으로 하여 양 옆값을 차이 m이하로 맞춘다.
 *  인덱스 5의 값만 1감소되어 5가 되고 (5, 5)가 pq에 들어온다.
 *            (5, 5)
 *      (6, 5)
 *  (7, 4)
 *  => 3 2 3 4 5
 *  이미 배열의 인접한 값들의 차이는 m이하이므로 배열은 아무 일도
 *  일어나지 않고 pq에서 값만 빠져나간다.
 *
 */

#include <iostream>
#include <queue>
using namespace std;
#define MXN 100002
typedef pair<int, int> pi;

int N, T;
int arr[MXN];
int ans[MXN];
int tarr[MXN];
priority_queue<pi> pq;

// m은 인접한 수들의 차이값의 최대값이다.
int solve(int m) {
	priority_queue<pi> tpq = pq;
	int cnt = 0;
	while (!tpq.empty()) {
		int cv = tpq.top().first;
		int ci = tpq.top().second;
		tpq.pop();

		if (ci > 0 && tarr[ci - 1] - m > tarr[ci]) {
			cnt += tarr[ci - 1] - tarr[ci] - m;
			tarr[ci - 1] = tarr[ci] + m;
			tpq.push({ tarr[ci - 1], ci - 1 });
		}
		if (ci < N-1 && tarr[ci + 1] - m > tarr[ci]) {
			cnt += tarr[ci + 1] - tarr[ci] - m;
			tarr[ci + 1] = tarr[ci] + m;
			tpq.push({ tarr[ci + 1], ci + 1 });
		}
		if (cnt > T) return cnt;
	}
	return cnt;
}

void bs(int s, int e) {
	while (s<=e) {
		for (int i = 0; i < N; i++) tarr[i] = arr[i];
		int m = (e + s) / 2;
		if (solve(m) > T) s = m + 1;
		else {
			for (int i = 0; i < N; i++) ans[i] = tarr[i];
			e = m - 1;
		}
	}
}

int main() {
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		pq.push({ arr[i], i });
		cin >> arr[i];
	}
	bs(0, 1e9);
	for (int i = 0; i < N; i++) cout << ans[i] << ' ';
	return 0;
}