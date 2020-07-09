// https://www.acmicpc.net/problem/2602
// 일반 DFS로 풀면 최악의 경우 시간초과 발생
// 메모이제이션을 이용하여 시간초과 해결

#include <iostream>
#include <string>
#include <cstring>
#define DEVIL 0
#define ANGEL 1
using namespace std;

string Scroll;      // 두루마리
string Bridge[2];   // 0은 악마 1은 천사
int N, S;           // N: 다리의 길이, S: 두루마리의 길이
int D[2][101][21];  // D[a][b][c] : -1로 초기화
                    // a번째 다리의 b번째 문자에서 두루마리의 c번째 문자를 찾을 때 Memoization
                    // -1이 아닌 경우, 이미 이전에 확인한 경우이기 때문에 해당 값을 바로 리턴 가능

int dfs(int bdg, int id = 0, int ch = 0) {
	if (ch == S)	// 두루마리 문자 끝까지 도달 = 다리를 건넘
		return 1;

	int& ret = D[bdg][id][ch];
	if (ret != -1)	// 이미 이전에 확인한 경우
		return ret;

	ret = 0;
	for (int i = id; i < N; i++) {
		if (Bridge[bdg][i] == Scroll[ch])
			ret += dfs(bdg ^ 1, i + 1, ch + 1);
	}
	return ret;
}

int main() {
	cin >> Scroll >> Bridge[DEVIL] >> Bridge[ANGEL];

	N = Bridge[0].length();
	S = Scroll.length();
	memset(D, -1, sizeof(D));

	cout << dfs(DEVIL) + dfs(ANGEL) << endl;
	return 0;
} 
