// https://www.acmicpc.net/problem/2239

// 계속 DFS가 끝까지 안 돌길래 뭐가 문제인가 한참 헤맸는데
// 알고보니 tmpCheck를 전역으로 선언해서 그런거였다..^^..
// 그걸 왜 전역으로 선언하냐고 멍청아 ㅠ
// 그리고 그 다음에는 Check 초기화와 동시에 Sudoku[x][y]를 0으로 안 해줘서 문제였다
// 단순한 백트래킹인데 왜 이렇게 오래 걸렸는지 모르겠다 ㅡㅡ

#include <iostream>
#include <cstring>
using namespace std;

int Sudoku[9][9];
bool Check[10][9][9];	// [i][j][k]: (j, k)에서 i가 올 수 있는지(false) 없는지(true)

void make_check(int n, int i, int j) {
	// 가로 세로
	for (int k = 0; k < 9; k++) {
		Check[n][i][k] = true;
		Check[n][k][j] = true;
	}
	// 3 * 3 영역
	i /= 3, i *= 3, j /= 3, j *= 3;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			Check[n][i + a][j + b] = true;
		}
	}
}

void dfs(int cnt = 0) {
	if (cnt == 81) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << Sudoku[i][j];
			}
			cout << endl;
		}
		exit(0);
	}

	int x = cnt / 9;
	int y = cnt % 9;
	bool tmpCheck[10][9][9];	// 이걸 전역으로 선언해줘서 한참 헤맴^^..
	memcpy(tmpCheck, Check, sizeof(Check));

	if (!Sudoku[x][y]) {
		for (int n = 1; n <= 9; n++) {
			if (!Check[n][x][y]) {
				Sudoku[x][y] = n;
				make_check(n, x, y);
				dfs(cnt + 1);
				Sudoku[x][y] = 0;	// 다시 초기화도!!
				memcpy(Check, tmpCheck, sizeof(Check));
			}
		}
	}
	else dfs(cnt + 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	char ch;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> ch;
			Sudoku[i][j] = ch - '0';
			if (Sudoku[i][j]) {
				make_check(Sudoku[i][j], i, j);
			}
		}
	}
	dfs();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << Sudoku[i][j];
		}
		cout << endl;
	}
	return 0;
}
