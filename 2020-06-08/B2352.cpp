// https://www.acmicpc.net/problem/2352
// LIS 문제인건 바로 알았는데 N 값이 너무 커서
// 내가 아는 O(N^2) 단순 DP 방법을 쓰면 당연히 시간초과가 날 것 같았다^^..
// 그래서 혹시나 시간복잡도가 더 작은 LIS 알고리즘이 있는지 찾아봤는데,
// 이분탐색을 이용한 O(NlgN) 방식이 있길래 해당 방식을 공부하고 풀었다.
// (탐색은 구현하기 귀찮아서 그냥 algorithm 헤더 썼다.. ㅎㅎㅎ)

#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Port[40001];
int DP[40001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Port[i];
	}
	
	int idx = 0;
	for (int i = 1; i <= N; i++) {
		if (DP[idx] < Port[i]) {
			DP[++idx] = Port[i];
		}
		else {
			int ii = lower_bound(DP, DP + idx, Port[i]) - DP;
			DP[ii] = Port[i];
		}
	}

	cout << idx << endl;
	return 0;
} 
