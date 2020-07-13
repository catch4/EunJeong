// https://www.acmicpc.net/problem/1806

#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 0x7FFFFFFF;
int N, S, Arr[100001], Answer = INF;

int main() {
	cin >> N >> S;
	for (int i = 0; i < N; i++) {
		cin >> Arr[i];
	}
	int sum = Arr[0];
	int high = 0, low = 0;

	while (low <= high && high < N) {
		if (sum < S) {
			sum += Arr[++high];
			continue;
		}
		Answer = min(Answer, (high - low + 1));
		if (sum == S) sum += Arr[++high];
		else if (sum > S) sum -= Arr[low++];
	}
	if (Answer == INF)
		cout << 0 << endl;
	else
		cout << Answer << endl;
	return 0;
}
