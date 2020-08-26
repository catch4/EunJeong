// https://www.acmicpc.net/problem/7579

// 처음에 가능한 COST의 범위도 1,000,000으로 봐서 시간 낭비했다. 문제를 잘 읽자..
// 시도하려는 cost를 0부터 1씩 늘려서 해당 cost에 M만큼 메모리를 확보할 수 있는지 찾았다.
// 0 -> 60 이상 확보 실패, 1 -> 실패, ... , 6 -> 성공! 6을 출력. 이런 식으로.

#include <iostream>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

const int MAXAPP = 100 + 1;
const int MAXCOST = 10000 + 1;
int N, M;
int Bytes[MAXAPP], Cost[MAXAPP];
int DP[MAXAPP][MAXCOST];	// DP[i][j]: i번째 앱에서 비용이 j일 때 확보할 수 있는 최대 메모리

int solve(int cost, int app = 0) {
	if (N <= app) return 0;

	int& ret = DP[app][cost];
	if (ret != -1)
		return ret;

	ret = solve(cost, app + 1);	// 현재 앱 비활성화 안 하는 경우
	// 현재 앱을 비활성화 하는 경우, 남은 비용보다 현재 앱의 비용이 작아야 차감할 수 있다.
	if (Cost[app] <= cost)
		ret = max(ret, Bytes[app] + solve(cost - Cost[app], app + 1));
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> Bytes[i];
	for (int i = 0; i < N; i++) cin >> Cost[i];
	memset(DP, -1, sizeof(DP));

	int cost = 0;
	while (true) {
		if (M <= solve(cost)) {
			cout << cost << endl;
			break;
		}
		cost++;
	}
	return 0;
}
