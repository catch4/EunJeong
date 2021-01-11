// https://www.acmicpc.net/problem/16432
// 순열처럼 풀었다

#include <iostream>
using namespace std;

int N;
int Arr[1001][11];
bool Check[1001][11];
int Ans[1001];

bool solve(int pos = 0, int prev = 0) {
	if (pos == N - 1) {
		for (int i = 1; i < 10; i++) {
			if (i == prev) continue;
			if (Arr[pos][i]) {
				Ans[pos] = i;
				return true;
			}
		}
	}
	for (int i = 1; i < 10; i++) {
		if (i == prev) continue;
		if (Arr[pos][i] && !Check[pos + 1][i]) {
			Check[pos + 1][i] = true;
			Ans[pos] = i;
			if (solve(pos + 1, i)) return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int b;
			cin >> b;
			Arr[i][b] = 1;
		}
	}
	if (solve()) {
		for (int i = 0; i < N; i++)
			cout << Ans[i] << endl;
	}
	else
    cout << "-1" << endl;
}
