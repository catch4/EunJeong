// https://www.acmicpc.net/problem/17780

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 12 + 1, MAXK = 10 + 1;
const int WHITE = 0, RED = 1, BLUE = 2;
const int dir[5][2] = { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
struct Piece {
	int num;
	int dir;
};
int N, K;
vector<Piece> Board[MAXN][MAXN];	// 각 칸마다 말 (0번이 가장 아래)
int Color[MAXN][MAXN];	// 각 칸의 색깔
pair<int, int> Loca[MAXK];	// i번 말의 위치

bool in_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int change_dir(int d) {
	if (d == 1 || d == 3) return d + 1;
	if (d == 2 || d == 4) return d - 1;
	return 0;
}

bool turn() {
	for (int i = 0; i < K; i++) {
		int x = Loca[i].first;
		int y = Loca[i].second;
		if (Board[x][y][0].num != i) continue;  // 가장 아래 말이 아닌 경우

		int d = Board[x][y][0].dir;
		int nx = x + dir[d][0];
		int ny = y + dir[d][1];

		if (!in_range(nx, ny) || Color[nx][ny] == BLUE) {
			d = Board[x][y][0].dir = change_dir(d);
			nx = x + dir[d][0];
			ny = y + dir[d][1];
      // 방향을 바꿨는데도 범위를 벗어나거나 파란색인 경우 말을 움직이지 않고 넘어간다.
      // 처음에 파란색인 것만 체크하고 !in_range(nx, ny) << 이 부분을 안 넣어줘서 런타임 에러가 났다.
			if (!in_range(nx, ny) || Color[nx][ny] == BLUE)
				continue;
		}
    
		// 문제에서는 빨간색일 때 반대로 올라가지만
    // vector의 push_back 때문에 제일 아래에 있는 말이 0번에 들어가므로
    // 흰색일 때 바꿔주고 빨간색일 때는 안 바꿔주는 걸로 구현이 됐다.
    if (Color[nx][ny] == WHITE)
			reverse(Board[x][y].begin(), Board[x][y].end());
		
    // 전체 말 다 옮겨주기
		while(!Board[x][y].empty()) {
			int size = Board[x][y].size();
			Piece tmp = Board[x][y][size - 1];
			Board[x][y].pop_back();
			Board[nx][ny].push_back(tmp);
			Loca[tmp.num] = { nx, ny };
		}
		if (4 <= Board[nx][ny].size()) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Color[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		x--; y--;
		Board[x][y].push_back({ i, d });
		Loca[i] = { x, y };
	}
	int ans = 0;
	while (true) {
		ans++;
		if (!turn()) break;
		if (1000 < ans) {
			ans = -1;
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
