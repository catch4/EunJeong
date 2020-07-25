// https://www.acmicpc.net/problem/14502
// 벽을 설치할 수 있는 모든 경우의 수마다 BFS로 바이러스를 퍼뜨리고 답 갱신.

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define EMPTY 0
#define WALL 1
#define VIRUS 2

const int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int N, M, Answer;
int Map[9][9], cpyMap[9][9];
bool Check[9][9];
vector<pair<int, int>> Empty;
vector<pair<int, int>> Virus;

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < M;
}

// 바이러스 퍼뜨리고 안전영역 갱신
void virus_spread() {
	queue<pair<int, int>> q;

	memcpy(cpyMap, Map, sizeof(Map));
	memset(Check, false, sizeof(Check));

	for (int i = 0; i < Virus.size(); i++) {
		q.push(Virus[i]);
		Check[Virus[i].first][Virus[i].second] = true;
	}
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;

		for (int d = 0; d < 4; d++) {
			int nr = r + dir[d][0];
			int nc = c + dir[d][1];

			if (in_range(nr, nc) && !Check[nr][nc] && !cpyMap[nr][nc]) {
				Check[nr][nc] = true;
				q.push({ nr, nc });
				cpyMap[nr][nc] = VIRUS;
			}
		}
		q.pop();
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (cpyMap[i][j] == EMPTY) ans++;
		}
	}
	if (Answer < ans) Answer = ans;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == EMPTY) Empty.push_back({ i, j });
			if (Map[i][j] == VIRUS) Virus.push_back({ i, j });
		}
	}
  // 벽을 세울 위치를 생성
	for (int i = 0; i < Empty.size() - 2; i++) {
		Map[Empty[i].first][Empty[i].second] = WALL;
		for (int j = i + 1; j < Empty.size() - 1; j++) {
			Map[Empty[j].first][Empty[j].second] = WALL;
			for (int k = j + 1; k < Empty.size(); k++) {
				Map[Empty[k].first][Empty[k].second] = WALL;
				virus_spread();
				Map[Empty[k].first][Empty[k].second] = EMPTY;
			}
			Map[Empty[j].first][Empty[j].second] = EMPTY;
		}
		Map[Empty[i].first][Empty[i].second] = EMPTY;
	}

	cout << Answer << endl;
	return 0;
} 
