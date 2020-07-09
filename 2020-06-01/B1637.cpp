// https://www.acmicpc.net/problem/1637

// O(logN)에 끝내야하는걸 보니 이분탐색인 건 알겠는데
// 이분탐색을 어떻게 활용해야할지 모르겠어서 그 부분을 검색해봄

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAX = 20001, INF = 0x7FFFFFFF;
int N;
ll A[MAX], B[MAX], C[MAX];

// mid보다 작거나 같은 수의 개수의 누적합 구하기
ll calc(ll mid) {
	ll ret = 0;
	for (int i = 0; i < N; i++) {
		if (A[i] <= mid)
			ret += ((min(mid, C[i]) - A[i]) / B[i] + 1);
	}
	return ret;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i] >> C[i] >> B[i];
	}

	ll left = 0, right = INF;
	while (left < right) {
		ll mid = (left + right) / 2;

		if (calc(mid) % 2 == 0) left = mid + 1;
		else right = mid;
	}
	// 이분탐색 중에서도 lower/upper bound 문제처럼..

	if (left == INF)
		cout << "NOTHING" << endl;
	else
		cout << left << " " << calc(left) - calc(left - 1) << endl;

	return 0;
}
