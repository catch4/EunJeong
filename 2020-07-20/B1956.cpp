// https://www.acmicpc.net/problem/1956

// 플로이드 와샬 알고리즘.
// 전에 했던 건데 기억이 안 나서 또 찾아봤다 ^^..

#include <iostream>
using namespace std;

const int MAX = 401;
const int INF = 0x7FFFFFFF;
int N, M;
int Graph[MAX][MAX];

int answer() {
	int min = INF;
	for (int i = 1; i <= N; i++) {
		if (Graph[i][i] < min) min = Graph[i][i];
	}
	if (min != INF) return min;
	else return -1;
}

void solve() {
	for (int i = 1; i <= N; i++) {	// 거쳐가는 노드
		for (int j = 1; j <= N; j++) {	// 시작 노드
			if (i == j) continue;
			for (int k = 1; k <= N; k++) {	// 도착 노드
				if (i == k) continue;
				if (Graph[j][k] > Graph[j][i] + Graph[i][k]) {
					Graph[j][k] = Graph[j][i] + Graph[i][k];
				}
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Graph[i][j] = INF;
		}
	}
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (c < Graph[a][b]) Graph[a][b] = c;
	}
	solve();
	cout << answer() << endl;
	return 0;
}
