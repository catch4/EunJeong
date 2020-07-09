// https://www.acmicpc.net/problem/1107

#include <iostream>
#include <cmath>
using namespace std;

int N, M, Answer;
bool isBroken[10];

// 고장난 버튼이면 0을 리턴하고, 가능한 경우면 자릿수 리턴
int check(int n) {
	if (n == 0) {
		if (isBroken[0]) return 0;
		else return 1;
	}
	// n = 0 일 때 예외 처리를 안 해줘서
	// while 문을 안 도는 바람에 계속 틀림 ㅠ_ㅠ
	int len = 0;
	while (n) {
		if (isBroken[n % 10])
			return false;
		n /= 10;
		len++;
	}
	return len;
}

int main() {
	cin >> N >> M;
	int tmp;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		isBroken[tmp] = true;
	}

	Answer = abs(100 - N);
	// 숫자 버튼이 모두 고장난 경우 || 이미 최솟값이라 계산이 필요 없는 경우
	if (M == 10 || (98 <= N && N <= 103)) {
		cout << Answer << endl;
		return 0;
	}

	// 888888까지만 돌려도 될 것 같은데.. ㅇ.ㅇ
	// 안 확실해서 그냥 안전하게 100만까지 돌림
	for (int i = 0; i <= 1000000; i++) {
		int len = check(i);
		if (len > 0) {
			tmp = len + abs(N - i);
			if (tmp < Answer)
				Answer = tmp;
		}
	}

	cout << Answer << endl;
	return 0;
}
