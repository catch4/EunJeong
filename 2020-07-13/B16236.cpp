// https://www.acmicpc.net/problem/16236

// 문제가 복잡해서 읽는데 엄청 오래 걸렸다..
// 사이즈 관련된 부분이 왜 이렇게 애매하게 있는건지;

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define SHARK 9

struct shark {
	int d, x, y;
	// 거리, 위치 순으로 정렬되도록
	bool operator < (const shark &s) const {
		if (d == s.d) {
			if (x == s.x) return y > s.y;
			else return x > s.x;
		}
		else return d > s.d;
	}
};

const int dx[4] = { -1, 0, 0, 1 }, dy[4] = { 0, -1, 1, 0 };

int N, Size = 2, Eat, Answer;
int Map[20][20];
bool Check[20][20];
priority_queue<shark> q;

bool in_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void bfs() {
	while (!q.empty()) {
		int d = q.top().d;
		int x = q.top().x;
		int y = q.top().y;
		q.pop();

		// 먹을 수 있는 경우
		if (0 < Map[x][y] && Map[x][y] < Size) {
			Map[x][y] = 0;
			Eat++;
			if (Eat == Size) {
				Size++;
				Eat = 0;
			}
			Answer += d;
      // 먹고 초기화
			d = 0;
			memset(Check, false, sizeof(Check));
			while (!q.empty()) q.pop();
		}
    // 물고기를 먹은 후 상어의 다음 위치
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!in_range(nx, ny) || Check[nx][ny]) continue;
			if (0 < Map[nx][ny] && Map[nx][ny] > Size) continue;
			// 상어의 위치를 상좌우하로 1씩 증가하고
			// 물고기를 먹기 전까지 거리를 1씩 키운다.
			q.push({ d + 1, nx, ny });
			Check[nx][ny] = true;
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == SHARK) {
				q.push({ 0, i, j });
				Map[i][j] = 0;
			}
		}
	}
	bfs();
	printf("%d\n", Answer);
	return 0;
}
