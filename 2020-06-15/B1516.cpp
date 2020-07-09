// https://www.acmicpc.net/problem/1516
// 예전에 위상정렬 문제는 풀어본 적이 있어서 구현은 쉽게 했다.
// 그러나 단순히 최솟값이라고 생각해서 29번째 줄의 max를 min으로 해서 틀렸다 ㅠ
// 우선 순위 중 가장 오래 걸리는 시간의 건물을 지어야 현재 건물을 지을 수 있다.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
int Time[502], Cnt[502], Answer[502];
vector<int> Graph[502];

void solve() {
	queue<int> q;

	for (int i = 1; i <= N; i++) {
		if (!Cnt[i]) {
			q.push(i);
			Answer[i] = Time[i];
		}
	}

	while (!q.empty()) {
		int curr = q.front();
		for (int i = 0; i < Graph[curr].size(); i++) {
			int next = Graph[curr][i];
			Answer[next] = max(Answer[next], Answer[curr] + Time[next]);
			if (--Cnt[next] == 0) {
				q.push(next);
			}
		}
		q.pop();
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Time[i];
		int x;
		while (cin >> x && x != -1) {
			Graph[x].push_back(i);
			Cnt[i]++;
		}
	}
	solve();
	for (int i = 1; i <= N; i++) {
		cout << Answer[i] << endl;
	}
	return 0;
}
