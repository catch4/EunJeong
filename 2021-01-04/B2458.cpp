// https://www.acmicpc.net/problem/2458

#include <iostream>
#include <vector>
using namespace std;

int N, M;
bool d[501][501];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		d[a-1][b-1] = 1;
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (d[i][k] && d[k][j]) d[i][j] = 1;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (!d[i][j] && !d[j][i]) cnt++;
		}
		if (!cnt) ans++;
	}
	cout << ans << endl;
	return 0;
}
