// https://www.acmicpc.net/problem/2661
// 처음에 아무 생각없이 1, 2, 3 중에서 가능한 경우를 붙여주는 경우로 풀었다가
// N = 7이 1213121에서 N = 8을 구할 때 1, 2, 3 모두 안 되는 경우가 발생했다
// 이럴 때 다시 7로 돌아가 1213123에서 N = 8인 경우를 구해야하므로 백트래킹이다.

#include <iostream>
#include <string>
using namespace std;

int N;

// 해당 수열이 좋은 수열인지 아닌지를 판단하는 함수
// 마지막 글자가 계속 추가되는 형태이기 때문에
// 뒤에서부터 인접한 부분 수열의 길이가 1일 때, 2일 때, ..., len / 2 때 확인
bool isGood(string str) {
	int len = str.length();
	for (int i = 1; i <= len / 2; i++) {
		bool good = false;
		int l = len - i * 2, r = len - i;
		for (int j = 0; j < i; j++) {
			if (str[l + j] != str[r + j]) {
				good = true;
			}
		}
		if (!good)
			return false;
	}
	return true;
}

void solve(int cnt = 0, string str = "") {
	if (cnt == N) {
		cout << str << endl;
		exit(0);
    // 처음 찾는 것이 결국 최솟값이기 때문에 바로 종료
	}

	for (char c = '1'; c <= '3'; c++) {
    // 일반 백트래킹에서 Check를 string의 push_back, pop_back으로 해줌
		str.push_back(c);
		if (isGood(str)) {
			solve(cnt + 1, str);
		}
		str.pop_back();
	}
}

int main() {
	cin >> N;
	solve();
	return 0;
}
