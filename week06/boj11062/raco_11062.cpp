/*
 *  BOJ 11062. 카드 게임
 *
 *  시간복잡도 : O(N^2)
 *  왼쪽에서 카드를 가져가는 횟수는 N번이 되며 왼쪽에서 가져가면서
 *  오른쪽에서 가져가는 횟수도 N번이 되므로 위와 같은 시간복잡도가
 *  나온다.
 *
 *  cache[l][r][t] : l~r의 카드 중 근우와 명우가 서로 최선을 다 했을 때 얻을 수 있는 근우의 최대 점수  
 *  
 *  처음 이 문제를 그리디 하게 왼쪽과 오른쪽 중에 가장 큰 값을 서로 가져가면
 *  된다고 생각했다. 하지만 예제 1, 2, 5, 2를 예로 들면 근우의 최대 점수는
 *  6이 되어야 하는데 5가 된다. 모든 경우를 봐주면서 시간을 줄이기 위해
 *  dp를 적용시켜 풀면 근우와 명우의 turn마다 근우의 turn에는 l ~ r까지의 
 *  고를 수 있는 최대값을 담고 명우의 turn에는 l ~ r 까지 고를 수 있는 최소값을 담는다.
 *
 *  인덱스는 one base, 1, 2, 5, 2를 다시 예로 들어 turn은 0부터 시작해서
 *  1~4까지의 카드가 있을 때 가장 큰 값을 구하기 위해서는 더 작은 부분문제의
 *  정답을 알아야 한다. 두 개의 부분 문제 1~3, 2~4가 풀려 있어야 한다.
 *  현재 부분 문제는 명우의 턴에서만 풀 수 있고 명우는 이 두 부분 문제 중
 *  더 작은 값을 리턴한다.(근우의 점수를 최소화 하기 위해) 이런식으로
 *  부분 문제를 먼저 구하여야 현재의 문제를 해결할 수 있기 때문에 재귀가
 *  적합하였고, 시간을 줄이기 위해 메모이제이션을 사용했다.
 *  
 */

#include <iostream>
#include <string.h>
using namespace std;
#define MXN 1002

int N;
int card[MXN];
int cache[MXN][MXN][2];

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

// 근우와 명우가 서로 최선을 다 했을 때 얻을 수 있는 근우의 최대 점수를 구한다.
int dfs(int l, int r, int t) {
	if (l == r) {
		if (t == 0) return card[l];
		else return 0;
	}

	int &ret = cache[l][r][t];
	if (ret != -1) return ret;


	if (t == 0)// 근우의 차례
		ret = max(dfs(l + 1, r, (t + 1) % 2) + card[l], dfs(l, r - 1, (t + 1) % 2) + card[r]);
	else// 명우의 차례
		ret = min(dfs(l + 1, r, (t + 1) % 2), dfs(l, r - 1, (t + 1) % 2));
	// 명우의 점수도 현재 카드에서 cache[l][r][1]
	// 에 가능한 최대 값을 담았다. 하지만 메모이제이션을 통해 이 값은 근우의
	// 값에도 영향을 미친다. 이 재귀함수는 근우의 점수를 구하는 함수이다.
	// 그렇다면 명우는 근우의 점수를 줄이기 위해 가능한 최소 점수를 ret에 담아 리턴한다.
	// 밑의 else문은 명우의 값을 최대로 해주어 틀린 코드이다.
	/*else {
		int ls = dfs(l + 1, r, (t + 1) % 2);
		int rs = dfs(l, r - 1, (t + 1) % 2);
		ret = max(ls + card[l], rs + card[r]);
		return min(ls, rs);
	}*/
	return ret;
}

int main() {
	int TC;
	cin >> TC;
	while (TC--) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> card[i];
		}
		memset(cache, -1, sizeof(cache));
		cout << dfs(0, N - 1, 0) << '\n';
	}
	return 0;
}