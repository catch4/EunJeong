#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAX = 50;

int Dir[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
int N, M;
int Answer;
int graph[MAX][MAX];
bool visited[MAX][MAX];

int bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;
	int cnt = 1;

	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		int bm = 1;
		for (int i = 0; i < 4; i++) {
			if (!(graph[cx][cy] & bm))
			{
				int nx = cx + Dir[i][0];
				int ny = cy + Dir[i][1];

				if (!(0 <= nx && nx < M && 0 <= ny && ny < N))
					continue;

				if (!visited[nx][ny]) {
					cnt++;
					visited[nx][ny] = true;
					q.push({ nx, ny });
				}
			}
			bm <<= 1;
		}
	}
	return cnt;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(false); cout.tie(false);
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> graph[i][j];
		}
	}

	int cnt = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j]) {
				Answer = max(Answer, bfs(i, j));
				cnt++;
			}
		}
	}

	cout << cnt << endl;
	cout << Answer << endl;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 1; k <= 8; k <<= 1) {
				if (graph[i][j] & k) {
					memset(visited, false, sizeof(visited));
					graph[i][j] -= k;
					Answer = max(Answer, bfs(i, j));
					graph[i][j] += k;
				}
			}
		}
	}

	cout << Answer << endl;
	return 0;
}
