// https://www.acmicpc.net/problem/14888
// 숫자 수열의 순서는 일정하게 정해져있고, 연산자의 우선순위도 똑같기 때문에
// 연산자를 수열처럼 생각하고 하나씩 숫자 사이에 넣어주면 됨

#include <iostream>
using namespace std;

// Max값이 음수가 될 수도 있는데 그 부분을 놓쳐서 한 번 틀림 ㅠ
int N, Max = 0x80000000, Min = 0x7FFFFFFF;
int Nums[12];
int Sign[4];    // + - * /

int calc(int a, int op, int b) {
	switch (op) {
	case 0:
		return a + b;
	case 1:
		return a - b;
	case 2:
		return a * b;
	case 3:
		return a / b;
	}
}

void dfs(int cnt = 1, int currVal = Nums[0]) {
	if (cnt == N) {
		if (Max < currVal) Max = currVal;
		if (Min > currVal) Min = currVal;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (Sign[i]) {
			Sign[i]--;
			dfs(cnt + 1, calc(currVal, i, Nums[cnt]));
			Sign[i]++;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> Nums[i];
	for (int i = 0; i < 4; i++)
		cin >> Sign[i];
	dfs();
	cout << Max << endl << Min << endl;
	return 0;
}
