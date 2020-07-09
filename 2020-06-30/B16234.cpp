// https://www.acmicpc.net/problem/16234
// BFS로 인구 이동이 일어나는 범위만큼 1, 2, ... N으로 번호를 설정해두고
// 설정된 번호마다 인구의 평균을 구해 대입해줌

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int N, L, R, Answer;
int Pop[51][51];
int Check[51][51];

int abs(int x) {
	return x < 0 ? -x : x;
}

bool in_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

// 인구 이동이 일어나는 나라에 같은 번호 부여하고 평균 인구 return
int bfs(int x, int y, int cnt) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	Check[x][y] = cnt;
	int sum = Pop[x][y], count = 1;

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;

		for (int d = 0; d < 4; d++) {
			int nr = r + dir[d][0];
			int nc = c + dir[d][1];

			if (!in_range(nr, nc) || Check[nr][nc]) continue;

			int diff = abs(Pop[r][c] - Pop[nr][nc]);
			if (L > diff || diff > R) continue;

			q.push({ nr, nc });
			Check[nr][nc] = cnt;
			sum += Pop[nr][nc];
			count++;
		}
		q.pop();
	}
	return sum / count;
}

bool move() {
	int cnt = 0;
	int avg_pop[51 * 51];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!Check[i][j]) {
				int tmp = bfs(i, j, ++cnt);
				avg_pop[cnt] = tmp;
			}
		}
	}
	if (cnt == N * N) return false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Pop[i][j] = avg_pop[Check[i][j]];
		}
	}
	return true;
}

void solve() {
  // 답이 2000이고 인구 이동이 일어날 때까지 반복
	while (Answer <= 2000 && move()) {
		Answer++;
		memset(Check, 0, sizeof(Check));
	}
}

int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Pop[i][j];
		}
	}
	solve();
	cout << Answer << endl;
	return 0;
}
