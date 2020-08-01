// https://www.acmicpc.net/problem/2342

// DP 문제 중에서 이런 유형이 제일 어려운 듯 ㅠㅠ
// DP의 인덱스를 어떻게 잡을건지만 정하면 되는데 (15번째 줄)
// 항상 그 부분이 잘 안되는 것 같다 ㅠㅠㅠ

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 0x7FFFFFFF;
int N;
int DDR[100001];
int DP[5][5][100001];	// [i][j][k]: 왼발이 i, 오른발이 j이고 k번째 DDR일 때

int calc(int prev, int curr) {
	if (prev == 0) return 2;
	else if (prev == curr) return 1;
	else if (abs(prev - curr) == 2) return 4;
	else return 3;
}

int solve(int left = 0, int right = 0, int cnt = 0) {
	if (cnt == N) return 0;

	int& ret = DP[left][right][cnt];
	if (ret != -1) return ret;

	ret = INF;
	ret = min(ret,
		  min(solve(DDR[cnt], right, cnt + 1) + calc(left, DDR[cnt]),
		      solve(left, DDR[cnt], cnt + 1) + calc(right, DDR[cnt])));
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(DP, -1, sizeof(DP));

	int step;
	while (cin >> step) {
		if (!step) break;
		DDR[N++] = step;
	}
	cout << solve() << endl;
	return 0;
}
