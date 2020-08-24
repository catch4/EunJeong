// https://www.acmicpc.net/problem/3109

#include <iostream>
#include <string>
#include <queue>
#define endl '/n'
using namespace std;

const int MAX = 10001;
const int dir[3][2] = { { -1, 1 }, {0, 1}, {1, 1} };

int R, C;
string Map[MAX];
bool Visit[MAX][500];

bool in_range(int r, int c) {
	return 0 <= r && r < R && 0 <= c && c < C
}

bool dfs(int r, int c) {
	Visit[r][c] = true;
	if (c == C - 1) return true;

	for (int i = 0; i < 3; i++) {
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		if (in_range(nr, nc)) {
			if (!Visit[nr][nc] && Map[nr][nc] == '.') {
				bool flag = dfs(nr, nc);
				if (flag)
					return flag;
			}
		}
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> R >> C;

	for (int i = 0; i < R; i++)
		cin >> Map[i];

	int answer = 0;
	for (int i = 0; i < R; i++)
		answer += dfs(i, 0);

	cout << answer << "\n";
	return 0;
}
