// https://www.acmicpc.net/problem/2159

#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

typedef long long ll;
const int Dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
const ll MAX = 200000000000;	// 최대 거리가 200,000이고 N이 100,000이니까 최댓값

int N;
vector<pair<int, int>> Guest;	// 0번째: 출발점, 그 뒤로 손님 좌표
ll DP[100001][5];	// 0부터 제자리, 상, 하, 좌, 우

int dist(pair<int, int> u, pair<int, int> v) {
	return abs(u.first - v.first) + abs(u.second - v.second);
}

// 재귀 DP
ll deliver(int curr = 0, int d = 0) {
	if (curr == N) return 0;

	ll& ret = DP[curr][d];
	if (ret != MAX) return ret; // 이미 구한 경우

	// 현재 좌표
	int x = Guest[curr].first + Dir[d][0];
	int y = Guest[curr].second + Dir[d][1];
	for (int i = 0; i < 5; i++) {
		// 다음 좌표
		int nx = Guest[curr + 1].first + Dir[i][0];
		int ny = Guest[curr + 1].second + Dir[i][1];
		if (0 < nx && nx <= 100000 && 0 < ny && ny <= 100000)
			ret = min(ret, deliver(curr + 1, i) + dist({ x, y }, { nx, ny }));
	}
	// 최솟값 메모이제이션
	return DP[curr][d] = ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	int a = 0, b = 0;
	for (int i = 0; i <= N; i++) {
		cin >> a >> b;
		Guest.push_back({ a, b });
	}
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < 5; j++) {
			DP[i][j] = MAX;
		}
	}
	deliver();
	cout << DP[0][0] << endl;
	return 0;
}
