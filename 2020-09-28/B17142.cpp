// https://www.acmicpc.net/problem/17142

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int EMPTY = 0, WALL = 1, VIRUS = 2;
const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
const int INF = 987654321;

int N, M, Answer = INF;
int Map[52][52], Check[52][52];
vector<pair<int, int>> V, Selected;

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < N;
}

int bfs() {
	queue<pair<int, int>> q;
	memset(Check, 0, sizeof(Check));

	for (auto& p : Selected) {
		int r = p.first;
		int c = p.second;
		q.push({ r, c });
		Check[r][c] = 1;
	}

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		int n = Check[r][c];
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (in_range(nr, nc) && Map[nr][nc] != WALL && !Check[nr][nc]) {
				Check[nr][nc] = n + 1;
				q.push({ nr, nc });
			}
		}
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] != WALL)
				if (!Check[i][j]) return -1;
			else
				if (Map[i][j] != VIRUS && ret < Check[i][j])
					ret = Check[i][j];
		}
	}
	return ret ? ret - 1 : 0;
}

void dfs(int id = 0, int cnt = 0) {
	if (M <= cnt) {
		int day = bfs();
		if (day == -1) return;
		if (day < Answer) Answer = day;
		return;
	}
	for (int i = id; i < V.size(); i++) {
		Selected.push_back(V[i]);
		dfs(i + 1, cnt + 1);
		Selected.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == VIRUS) {
				V.push_back({ i, j });
			}
		}
	}
	dfs();
	if (Answer == INF) cout << "-1\n";
	else cout << Answer << '\n';
	return 0;
}
