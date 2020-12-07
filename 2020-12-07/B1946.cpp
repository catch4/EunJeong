// https://www.acmicpc.net/problem/1946

#include <iostream>
#include <algorithm>
using namespace std;

int N;
pair<int, int> Score[100001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			int a, b;
			cin >> a >> b;
			Score[i] = { a, b };
		}
		sort(Score, Score + N);
		int pos = 0, answer = 1;
		for (int i = 1; i < N; i++) {
			if (Score[pos].second > Score[i].second) {
				answer++;
				pos = i;
			}
		}
		cout << answer << endl;
	}
	return 0;
}
