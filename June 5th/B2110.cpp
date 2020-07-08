// https://www.acmicpc.net/problem/2110
// 이분탐색으로 거리를 조정하면서 설치 가능한 공유기의 개수를 센다.

#include <iostream>
#include <algorithm>
using namespace std;

int N, C, Answer;
int House[200000];

int main() {
	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		cin >> House[i];
	}
	sort(House, House + N);
	int left = 1;
	int right = House[N - 1] - House[0];

	while (left <= right) {
		int gap = (left + right) / 2;
		int cnt = 1;

		int tmp = House[0];
		for (int i = 1; i < N; i++) {
			if (gap <= House[i] - tmp) {
				cnt++;
				tmp = House[i];
			}
		}
		if (C <= cnt) {
			Answer = gap;
			left = gap + 1;
		}
		else {
			right = gap - 1;
		}
	}
	cout << Answer << endl;
	return 0;
}
