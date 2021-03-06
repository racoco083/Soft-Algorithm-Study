/*
BOJ 1089 - 엘리베이터

num 배열에 0~9까지의 전구 모양을 넣어둡니다.
입력받은 안내판 정보 한 글자씩 dfs2에서 그 글자에서 나올 수 숫자를 완전탐색하여 vec에 넣어줍니다.
숫자 판별은 what 함수에서 합니다. 0~9 숫자중 일치하는 게 있다면 그 수를 반환, 없다면 -1을 반환합니다.

나올 수 있는 수의 가짓수는 각 자릿수의 나올 숫자 가짓수를 모두 곱한 값이 됩니다.
최대 9^9 가지 이므로 완전탐색으로는 TLE를 받게됩니다.
다른 방법을 생각해 봤는데, 각 자릿수별로 숫자는 무족건 선택이 되어야하니
숫자*(10^자릿수)*(현재 자릿수를 제외한 모든 경우) 만큼 합에 더해주면 됩니다.
*/
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

char st[5][40];
vector<int> vec[10];
int n;
ll sum, cnt;
char num[10][5][3] = {
{ '#','#','#','#','.','#','#','.','#','#','.','#','#','#','#' },
{ '.','.','#','.','.','#','.','.','#','.','.','#','.','.','#' },
{ '#','#','#','.','.','#','#','#','#','#','.','.','#','#','#' },
{ '#','#','#','.','.','#','#','#','#','.','.','#','#','#','#' },
{ '#','.','#','#','.','#','#','#','#','.','.','#','.','.','#' },
{ '#','#','#','#','.','.','#','#','#','.','.','#','#','#','#' },
{ '#','#','#','#','.','.','#','#','#','#','.','#','#','#','#' },
{ '#','#','#','.','.','#','.','.','#','.','.','#','.','.','#' },
{ '#','#','#','#','.','#','#','#','#','#','.','#','#','#','#' },
{ '#','#','#','#','.','#','#','#','#','.','.','#','#','#','#' } };

int what(int c) {  // 수 판별
	int j, k;
	for (int i = 0; i <= 9; i++) {
		for (j = 0; j < 5; j++) {
			for (k = 0; k < 3; k++) {
				if (num[i][j][k] != st[j][k+c]) break;
			}
			if (k != 3) break;
		}
		if (j == 5) return i; // 모두 일치
	}
	return -1; // 일치하는 수 없음
}
void dfs2(int cc, int u) {  // 나올 수 있는 숫자 완탐
	if (cc == 15) {
		int nnn = what(u);
		if (nnn != -1)
			vec[u/4].push_back(nnn);
		return;
	}
	int nr = cc / 3, nc = cc % 3 + u;
	if (cc == 4 || cc == 10) dfs2(cc + 1, u); // 항상 꺼져있을 위치
	else {
		if (st[nr][nc] == '.') {
			st[nr][nc] = '#';
			dfs2(cc + 1, u);
			st[nr][nc] = '.';
			dfs2(cc + 1, u);
		}
		else dfs2(cc + 1, u);
	}
}
int main() {
	ll gaji = 1, x = 1, y = 0;
	scanf("%d", &n);
	for (int i = 0; i < 5; i++) {
		scanf("%s", st[i]);
	}
	for (int i = 0; i < 4 * n - 1; i += 4) {
		dfs2(0, i);
	}
	for (int i = 0; i < n; i++) {
		gaji *= vec[i].size();  // 모든 가짓수
	}
	for (int i = n-1; i >=0; i--) {
		for (int &v : vec[i]) {
			if (i == 0 && v == 0) continue;
			sum += gaji / vec[i].size() *v*x;
		}
		x *= 10;
	}
	if (gaji==0) printf("-1");
	else printf("%Lf", (long double)sum / gaji);

	return 0;
}