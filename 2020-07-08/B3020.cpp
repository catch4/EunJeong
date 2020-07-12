// https://www.acmicpc.net/problem/3020

// 높이에 따라 석순과 종유석의 수를 카운트하고
// 누적합을 구하면 H로 날 때 부딪히는 석순과 종유석을 알 수 있다.

#include <iostream>
using namespace std;

int N, H;
int A[500001];	// 높이가 i인 석순의 개수
int B[500001];	// 높이가 i인 종유석의 개수
int Count[200001];

int main() {
	cin >> N >> H;
	for (int i = 0; i < N; i++) {
		int height;
		cin >> height;
		if (i % 2 == 0) A[height]++;
		else B[height]++;
	}

	for (int i = H; 0 < i; i--) {
		A[i - 1] += A[i];
		B[i - 1] += B[i];
	}

	int min = N;
	for (int i = 1; i <= H; i++) {
		int tmp = A[i] + B[H - i + 1];
		Count[tmp]++;
		if (tmp < min) min = tmp;
	}

	cout << min << " " << Count[min] << endl;
	return 0;
}
