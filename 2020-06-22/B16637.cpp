// https://www.acmicpc.net/problem/16637

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int N, Answer = 0x7FFFFFFF;
string Eq;

int calc(int a, char oper, int b) {
	switch (oper) {
	case '+': return a + b;
	case '*': return a * b;
	case '-': return a - b;
	}
	return a;
}

void dfs(int idx = 0, int val = 0) {
	if (idx == N) {
		if (Answer < val)
			Answer = val;
		return;
	}
	char oper = (idx == 0) ? '+' : Eq[idx - 1];	// 이전 기호
	if (idx + 2 < N) {
		int tmp = calc(Eq[idx] - '0', Eq[idx + 1], Eq[idx + 2] - '0');	// 괄호를 묶어서 계산한 값
		dfs(idx + 4, calc(val, oper, tmp));	// 이전 기호로 현재까지 계산 결과와 tmp를 계산
	}
	dfs(idx + 2, calc(val, oper, Eq[idx] - '0'));	// 괄호를 묶지 않은 경우
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> Eq;
	dfs();
	cout << Answer << endl;
	return 0;
} 
