// https://www.acmicpc.net/problem/17244

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define WALL '#'
#define START 'S'
#define END 'E'
#define THING 'X'
const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int N, M, K, Answer = 0x7FFFFFFF;
pair<int, int> Start, End;
char House[51][51];
int Visit[51][51];
int Steps[7][7];	// i부터 j까지 걸음 수 (0은 시작점, K + 1은 도착점)
bool Check[7];
vector<pair<int, int>> Things;	// 시작점, 챙길 물건, 도착점이 모두 들어있는 벡터

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < M;
}

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	Visit[x][y] = 1;

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		int d = Visit[r][c];

		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];

			if (in_range(nr, nc) && House[nr][nc] != WALL && !Visit[nr][nc]) {
				q.push({ nr, nc });
				Visit[nr][nc] = d + 1;
			}
		}
		q.pop();
	}
}

// bfs를 통해 계산한 거리를 Steps 배열에 넣어줌
void calc_steps(int num) {
	int x = Things[num].first, y = Things[num].second;
	bfs(x, y);
	for (int i = 0; i < Things.size(); i++) {
		if (i == num) continue;
		Steps[num][i] = Visit[Things[i].first][Things[i].second] - 1;
	}
	memset(Visit, 0, sizeof(Visit));
}

// dfs로 수열 생성하면서 걸음수를 계산
void dfs(int prev = 0, int steps = 0, int cnt = 0) {
	if (cnt == K) {
		steps += Steps[prev][K + 1];
		if (steps < Answer)
			Answer = steps;
		return;
	}

	for (int i = 1; i <= K; i++) {
		if (!Check[i]) {
			Check[i] = true;
			dfs(i, steps + Steps[prev][i], cnt + 1);
			Check[i] = false;
		}
	}
}

void solve() {
	for (int i = 0; i < Things.size(); i++)
		calc_steps(i);
	dfs();
}

int main() {
	cin >> M >> N;
	Things.push_back({ 0, 0 });
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> House[i][j];
			if (House[i][j] == START) Start = { i, j };
			if (House[i][j] == END) End = { i, j };
			if (House[i][j] == THING) {
				K++;
				Things.push_back({ i, j });
			}
		}
	}
	Things[0] = Start;
	Things.push_back(End);

	solve();
	cout << Answer << endl;
	return 0;
} 
