// https://www.acmicpc.net/problem/14503

#include <iostream>
using namespace std;

const int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };	// 북 동 남 서
int N, M;
struct RobotVaccum {
	int r; int c; int d;
} RV;
int Room[51][51];
bool Visit[51][51];
int Answer;

bool in_range(int r, int c) {
	return (0 <= r && r < N && 0 <= c && c < M);
}

void clean() {
	int r = RV.r;
	int c = RV.c;
	int d = RV.d;

	// 현재 위치 청소
	if (!Visit[r][c]) {
		Answer++;
		Visit[r][c] = true;
	}
	
	// 현재 방향 기준 왼쪽 방향으로 돌아서
	for (int i = 1; i < 5; i++) {
		int nd = (((d - i) % 4) + 4) % 4;
		int nr = r + dir[nd][0];
		int nc = c + dir[nd][1];

		// 청소 가능(아직 청소 안 한 빈 칸)하면 해당 방향으로 이동하고 다시 청소
		if (!Room[nr][nc] && !Visit[nr][nc] && in_range(nr, nc)) {
			RV.r = nr; RV.c = nc; RV.d = nd;
			clean();
			return;
		}
	}

	// 다 돌았는데 청소할 곳이 없으면 후진
	int nr = r - dir[d][0];
	int nc = c - dir[d][1];

	// 후진 못 하면 작동 종료
	if (Room[nr][nc])
		return;

	// 후진해서 다시 청소
	RV.r = nr; RV.c = nc;
	clean();
}

int main() {
	cin >> N >> M;
	cin >> RV.r >> RV.c >> RV.d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Room[i][j];
		}
	}
	clean();
	cout << Answer << endl;
	return 0;
}
