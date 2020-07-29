// https://www.acmicpc.net/problem/6593

// 평소하던 BFS에 방향만 추가해주면 돼서 간단한게 구현 가능.
// 처음에 메모리 초과가 나길래 함수 안에 있던 큐를 전역으로 빼주는 뻘짓을 했는데
// 알고보니 bfs에서 visit 체크를 안 한거였다^^.. ㅋㅋㅋㅋ 하..
// 제발 당연하고 이상한 걸로 실수하지 말자!!

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

const int dir[6][3] = { {0, 0, 1}, {0, 1, 0}, {0, 0, -1}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0} };
struct Point {
	int l, r, c;
};
int L, R, C;	// 층, 행, 열
char Building[31][31][31];
int Visit[31][31][31];
Point Start, End;

bool in_range(int l, int r, int c) {
	return 0 <= l && l < L && 0 <= r && r < R && 0 <= c && c < C;
}

void bfs(int l, int r, int c) {
	queue<Point> q;
	q.push({ l, r, c });
	Visit[l][r][c] = 1;

	while (!q.empty()) {
		int cl = q.front().l;
		int cr = q.front().r;
		int cc = q.front().c;
		int ct = Visit[cl][cr][cc];
		q.pop();

		for (int i = 0; i < 6; i++) {
			int nl = cl + dir[i][0];
			int nr = cr + dir[i][1];
			int nc = cc + dir[i][2];

			if (nl == End.l && nr == End.r && nc == End.c) {
				cout << "Escaped in " << ct << " minute(s)." << endl;
				return;
			}

			if (in_range(nl, nr, nc) && !Visit[nl][nr][nc] && Building[nl][nr][nc] == '.') {
				q.push({ nl, nr, nc });
				Visit[nl][nr][nc] = ct + 1;
			}
		}
	}
	cout << "Trapped!" << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> L >> R >> C) {
		if (!(L || R || C)) break;
		memset(Visit, 0, sizeof(Visit));
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < R; j++) {
				for (int k = 0; k < C; k++) {
					cin >> Building[i][j][k];
					if (Building[i][j][k] == 'S')
						Start = { i, j, k };
					else if (Building[i][j][k] == 'E')
						End = { i, j, k };
				}
			}
		}
		bfs(Start.l, Start.r, Start.c);
	}
	return 0;
}
