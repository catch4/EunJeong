// https://www.acmicpc.net/problem/2146

// 전역 큐와 지역 큐를 같이 돌리느라 좀 헷갈렸다.
// 지역 큐(q)의 BFS를 통해 같은 섬을 찾으면서 동시에 전역 큐에 push해주고,
// 전역 큐(Q)의 BFS를 통해서는 다른 섬을 만나는 즉시 그 때의 거리를 return해서
// 섬마다 최솟값을 갱신하도록 했다.

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int N, Answer = 0x7FFFFFFF;
int Map[101][101];
bool Visited[101][101];
int Dist[101][101];
queue<pair<int, int>> Q;

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < N;
}

void sameIsland(int x, int y) {
	Q.push({ x, y });
	Dist[x][y] = 0;
	Visited[x][y] = true;

	queue<pair<int, int>> q;
	q.push({ x, y });

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (in_range(nr, nc) && !Visited[nr][nc] && Map[nr][nc]) {
				Q.push({ nr, nc });
				Dist[nr][nc] = 0;
				Visited[nr][nc] = true;

				q.push({ nr, nc });
			}
		}
	}
}

int calcDist() {
	while (!Q.empty()) {
		int r = Q.front().first;
		int c = Q.front().second;
		int d = Dist[r][c];

		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (in_range(nr, nc) && Dist[nr][nc] == -1) {
				if (Map[nr][nc]) return d + 1;
				Q.push({ nr, nc });
				Dist[nr][nc] = d + 1;
			}
		}
		Q.pop();
	}
	return -1;
}

void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] && !Visited[i][j]) {
				memset(Dist, -1, sizeof(Dist));
				sameIsland(i, j);	// 같은 섬 찾으면서 전역 큐에 전부 push, Dist 0으로 설정

				int min = calcDist() - 1;		// 거리의 최솟값
				if (min < Answer) Answer = min;	// 최솟값 갱신

				while (!Q.empty()) Q.pop();		// 큐 비워주기
			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Map[i][j];

	solve();
	cout << Answer << endl;
	return 0;
}
