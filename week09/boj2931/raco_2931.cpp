/*
 *  BOJ 2931. 가스관
 *
 *  시간복잡도 : O(RC)
 *
 *  문제의 설명에 항상 답이 존재하고, 가스의 흐름이 유일한 경로만 입력으로
 *  주어지고, 불필요한 블럭은 존재하지 않고, 없어진 블록을 추가하면 모든
 *  블럭에 가스가 흐르게 된며, 모스크바와 자그레브가 하나의 블럭과 인접해 있는
 *  입력만 주어진다. 
 *
 *  결국 '.'인 영역의 좌우상하 네 방향에서 현재 정점으로 연결되어 있는
 *  블럭들이 있으면 현재 영역은 그 블록으로 갈 때의 방향값을 비트로 
 *  담아주면 된다. 북 1, 동 2, 남 4, 서 8  <= bit
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 26
typedef pair<int, int>  pi;

int R, C;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
char area[MXN + 1][MXN + 1];
int block[MXN + 1][MXN + 1];
int ans;

//  방향들의 값을 통해 블럭을 찾는다.
char get_block(int dir) {
	char ret = '|';
	if (dir == 10) ret = '-';
	else if (dir == 15) ret = '+';
	else if (dir == 6) ret = '1';
	else if (dir == 3) ret = '2';
	else if (dir == 9) ret = '3';
	else if (dir == 12) ret = '4';
	return ret;
}

// 해당 블럭의 모든 방향들 값을 담아 리턴한다.
int get_dir(char c) {
	int ret = 5;// '|'을 담아 놓는다.
	if (c == '-') ret = 10;
	else if (c == '+') ret = 15;
	else if (c == '1') ret = 6;
	else if (c == '2') ret = 3;
	else if (c == '3') ret = 9;
	else if (c == '4') ret = 12;
	return ret;
}

// 현재 영역(y, x)이 사라진 블럭이 있었던 영역인지 아닌지를 알려준다.
bool is_db(int y, int x) {// is_disappear_block
	bool ret = false;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= R || nx < 0 || nx >= C || area[ny][nx] == '.') continue;
		// 현재 영역의 방향은 i인데 이 방향에 있는 블럭이 반대 방향((i + 2) % 4))으로
		// 열려 있는지 체크하고 열려있으면 이 영역은 사라진 블럭이 있던 영역이고
		// 현 영역을 원래 방향값을 ans에 누적한다.
		if (block[ny][nx] & (1 << ((i + 2) % 4))) {
			ans |= (1 << i);
			ret = true;
		}
	}
	return ret;
}

int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> area[i][j];
			if (area[i][j] != '.' && area[i][j] != 'M' && area[i][j] != 'Z') block[i][j] = get_dir(area[i][j]);
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (area[i][j] != '.') continue;
			if (is_db(i, j)) {
				cout << i + 1 << ' ' << j + 1 << ' ' << get_block(ans) << '\n';
				return 0;
			}
		}
	}
	return 0;
}