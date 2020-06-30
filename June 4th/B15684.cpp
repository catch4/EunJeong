// https://www.acmicpc.net/problem/15684

#include <iostream>
#define endl '\n'
using namespace std;

int N, M, H, Answer;
bool Visit[11][30];

int min(int a, int b) {
	return a < b ? a : b;
}

bool ladder() {
	for (int i = 1; i <= N; i++) {
		int curr = i;
		for (int j = 1; j <= H; j++) {
			if (Visit[curr][j]) curr += 1;
			else if (Visit[curr - 1][j]) curr -= 1;
		}
		if (curr != i) return false;
	}
	return true;
}

void dfs(int idx = 1, int cnt = 0) {
	if (3 < cnt) return;

	if (ladder() == true) {
		Answer = min(Answer, cnt);
		return;
	}

	for (int i = idx; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			if (!Visit[j][i] && !Visit[j - 1][i] && !Visit[j + 1][i]) {
				Visit[j][i] = true;
				dfs(i, cnt + 1);
				Visit[j][i] = false;
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	Answer = 0x7FFFFFFF;
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		Visit[b][a] = true;
	}

	dfs();
	if (Answer == 0x7FFFFFFF) Answer = -1;
	cout << Answer << endl;

	return 0;
}
