// https://www.acmicpc.net/problem/12904

// 처음에 아무 생각없이 모든 경우의 수 탐색하다가.. 당연히 시간 초과나는 걸 깨달음
// 반대로 T에서 S를 만들 수 있는지 생각해보면 더 간단함

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string S, T;
bool Result;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> S >> T;

	while (true) {
		if (S.length() == T.length()) {
			if (S == T) Result = true;
			break;
		}
		char c = *(--T.end());
		T.pop_back();
		if (c == 'B')
			reverse(T.begin(), T.end());
	}
	cout << Result << endl;

	return 0;
}
