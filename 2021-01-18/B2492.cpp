// https://www.acmicpc.net/problem/2492

// 틀린 이유 [1]
// 보석이 변이 아니라 모서리에 있는 경우 중에 하나가 답이 될 것이라고 생각

// 틀린 이유 [2]
// 40 ~ 42: K를 더했을 때 범위가 넘어가는 경우 확인을 하지 않았음

#include <iostream>
#include <vector>
using namespace std;

int N, M, T, K;
vector<pair<int, int>> Gems;

// 좌하 모서리 점을 받아서 보석의 개수를 셈
int count(int x, int y) {
	int ret = 0;
	for (auto g : Gems) {
		if (x <= g.first && g.first <= x + K && y <= g.second && g.second <= y + K)
			ret++;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> T >> K;
	for (int i = 0; i < T; i++) {
		int a, b;
		cin >> a >> b;
		Gems.push_back({ a, b });
	}
  
	int answer = 0, ans_x = 0, ans_y = 0;
	for (auto x : Gems) {
		for (auto y : Gems) {
			// K를 더해서 범위가 넘어갈 경우 N - K, M - K 도 확인
			int xx = (N < x.first + K) ? N - K : x.first;
			int yy = (M < y.second + K) ? M - K : y.second;
			int tmp = count(xx, yy);
			if (answer < tmp) {
				answer = tmp;
				ans_x = xx, ans_y = yy + K; // 좌상 모서리 점으로 바꿔줌
			}
		}
	}
  
	cout << ans_x << ' ' << ans_y << '\n' << answer << '\n';
	return 0;
}
