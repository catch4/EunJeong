// https://www.acmicpc.net/problem/13422

// 100%에서 틀렸습니다 뜨길래 뭔가 했더니
// 25번째 줄 추가 안 해줘서 계속 틀린 거였다 ㅠ

#include <iostream>
using namespace std;

int N, M, K;
int Money[100001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M >> K;
		int sum = 0, ans = 0;
		for (int i = 0; i < N; i++) {
			cin >> Money[i];
			if (i < M) sum += Money[i];
		}

		// N과 M이 같으면 한 가지 경우만 보면 된다.
		if (N == M) ans = (sum < K) ? 1 : 0;
		else {
			for (int i = 0; i < N; i++) {
				if (sum < K) ans++;
				int j = (i + M) % N;
				sum -= Money[i];
				sum += Money[j];
			}
		}
		cout << ans << endl;
	}
	return 0;
}
