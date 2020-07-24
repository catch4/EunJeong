// https://www.acmicpc.net/problem/3980

// 테스트 케이스 여러개 돌리는 문제를 너무 오랜만에 풀어봐서
// Answer을 초기화 안 시켜주는 바람에 한 번 틀렸다 ^^..
// 기본적으로는 비트마스크를 이용한 dfs를 구현했다.

#include <iostream>
using namespace std;

int Players[11][11];
int Answer;

void dfs(int cnt = 0, int bm = 0, int sum = 0) {
	if (cnt == 11) {
		if (Answer < sum)
			Answer = sum;
		return;
	}
	for (int i = 0; i < 11; i++) {
		if (!Players[cnt][i]) continue;
		if (bm & (1 << i)) continue;
		dfs(cnt + 1, bm | (1 << i), sum + Players[cnt][i]);
	}
}

int main() {
	int T;
	cin >> T;

	while (T--) {
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cin >> Players[i][j];
			}
		}
		Answer = 0;
		dfs();
		cout << Answer << endl;
	}
	return 0;
}
