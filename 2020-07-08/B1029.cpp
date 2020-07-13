// https://www.acmicpc.net/problem/1209

// MAX_SIZE가 15여서 그대로 dfs돌리면 15!으로 시간초과가 날 것.
// 그래서 각각의 경우에 대해 메모이제이션을 했다.

#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 15;
int N, Answer;
int Price[MAX_SIZE][MAX_SIZE];
int Memo[MAX_SIZE][10][1 << MAX_SIZE];	// Memoization: artist, cost, state

int dfs(int artist = 0, int currCost = 0, int state = 1, int ans = 1) {
	int& ret = Memo[artist][currCost][state];

	if (ret)
		return ret;

	ret = ans;
	for (int i = 0; i < N; i++) {
		if (state & (1 << i) || Price[artist][i] < currCost) continue;
		ret = max(ret, dfs(i, Price[artist][i], state | (1 << i), ans + 1));
	}
	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &Price[i][j]);
		}
	}
	printf("%d\n", dfs());
	return 0;
}
