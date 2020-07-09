// https://www.acmicpc.net/problem/2178
#include <iostream>
#include <queue>
using namespace std;

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int N, M;
int Maze[101][101];
int Check[101][101];

bool in_range(int r, int c) {
	return (0 <= r && r < N && 0 <= c && c < M);
}

void bfs() {
	queue<pair<int, int>> q;
	q.push({ 0, 0 });
	Check[0][0] = 1;

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		int d = Check[r][c];

		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (in_range(nr, nc) && Maze[nr][nc] && !Check[nr][nc]) {
				Check[nr][nc] = d + 1;
				q.push({ nr, nc });
			}
		}
		q.pop();
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char c;
			cin >> c;
			if (c == '1') Maze[i][j] = 1;
			else Maze[i][j] = 0;
		}
	}
	bfs();
	cout << Check[N - 1][M - 1] << endl;
	return 0;
} 
