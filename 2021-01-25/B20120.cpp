// https://www.acmicpc.net/problem/20120

// 1. 18번 줄에서 기저 조건에서 리턴할 때 ret = 0 안 해줘서 틀림
// 2. i가 최대 1001까지 나오는데 배열 크기 1002 이상으로 안 해줘서 틀림

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int N;
ll Note[1002];
ll DP[1002][1002][3]; // [i][j][k]: i번째 노트에서 j번 콤보이고 연속 미스가 k번
bool Check[1002][1002][3];

ll solve(int i = 1, int j = 1, int k = 0) {
	ll &ret = DP[i][j][k];
	if (i == N + 1) return ret = 0;
	if (Check[i][j][k]) return ret;
	Check[i][j][k] = true;
	// 이번 노트를 친 경우
	ret = solve(i + 1, j + 1, 0) + (Note[i] * j);
	// 이번 노트를 놓친 경우
	if (k < 2) ret = max(ret, solve(i + 1, 1, k + 1));
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Note[i];
	}
	cout << max(solve(), 0ll) << endl;
	return 0;
}
