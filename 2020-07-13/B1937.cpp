// https://www.acmicpc.net/problem/1937
// N이 500이므로 그냥 dfs를 사용하면 시간 초과.
// dfs에 memoization을 썼다. 자주 보이는 유형인 듯.
// DP 배열에는 각 경우에서의 최대길이가 저장되어 있다.

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int N;
int Map[501][501];
int DP[501][501];

bool in_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int dfs(int x, int y) {
	int& ret = DP[x][y];
	if (ret) return ret;

	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (in_range(nx, ny) && Map[x][y] < Map[nx][ny]) {
			ret = max(ret, dfs(nx, ny));
		}
	}
	return DP[x][y] = ret + 1;
}

void solve() {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int tmp = dfs(i, j);
			if (ans < tmp) ans = tmp;
		}
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}
	solve();
	return 0;
}
