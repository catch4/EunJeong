// https://www.acmicpc.net/problem/4485
// 처음에 단순하게 최단거리일 때만 최솟값이 나올 것이라고 생각하고 BFS로 풀었는데
// 예제 2번에서 최단거리가 아닌, 돌아갈 때 최솟값이 나오는 경우가 생겼다 ㅠㅠ (멍-청)
// 다시 생각해보니 DFS 아니면 다익스트라로 풀어야할 것 같아서 일단 DFS + DP로 풀었는데 시간초과..^_^
// DFS + DP가 N값이 100 정도일 때는 괜찮은데 125라서 그런 것 같다 ㅠ 결국은 다익스트라로...

#include <iostream>
#include <queue>
using namespace std;
const int dir[4][2] = { {0, 1}, {1, 0}, { 0, -1 }, {-1, 0} };

int N;
int Map[126][126];
int Rupee[126][126];

bool in_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int djikstra() {
	Rupee[0][0] = Map[0][0];
	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({ -Rupee[0][0], { 0, 0 } });

	while (!pq.empty()) {
		int x = pq.top().second.first;
		int y = pq.top().second.second;
		int c = -pq.top().first;
		pq.pop();

		if (Rupee[x][y] < c) continue;

		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			if (in_range(nx, ny)) {
				int nc = c + Map[nx][ny];
				if (nc < Rupee[nx][ny]) {
					Rupee[nx][ny] = nc;
					pq.push({ -nc, {nx, ny} });
				}
			}
		}
	}
	return Rupee[N - 1][N - 1];
}

int main() {
	int tc = 1;
	while (cin >> N && N) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> Map[i][j];
				Rupee[i][j] = 0x7FFFFFFF;
			}
		}
		cout << "Problem " << tc++ << ": " << djikstra() << endl;
	}
	return 0;
}

// DFS + Memoization으로 시도한 풀이
//void dfs(int r = 0, int c = 0) {
//	if (r == N - 1 && c == N - 1) return;
//
//	for (int i = 0; i < 4; i++) {
//		int nr = r + dir[i][0];
//		int nc = c + dir[i][1];
//		if (in_range(nr, nc) && !Visit[nr][nc]) {
//			int curr = DP[r][c] + Map[nr][nc];
//			if (DP[nr][nc] && DP[nr][nc] <= curr) continue;
//			if (DP[N - 1][N - 1] && DP[N - 1][N - 1] <= curr) continue;
//			DP[nr][nc] = curr;
//
//			Visit[nr][nc] = true;
//			dfs(nr, nc);
//			Visit[nr][nc] = false;
//		}
//	}
//}
