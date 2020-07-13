// https://www.acmicpc.net/problem/10159

// 입력이 i j로 들어올 때 i -> j인 방향 그래프로 만들어준다.
// 입력을 모두 받은 뒤 BFS로 각 순서쌍마다 경로가 존재하는지 확인.

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 101;
int N, M;
vector<int> Graph[MAX];
bool Check[MAX];

bool bfs(int from, int to) {
	if (from == to) return true;

	memset(Check, false, sizeof(Check));
	queue<int> q;
	q.push(from);
	Check[from] = true;

	while (!q.empty()) {
		int curr = q.front();
		for (int i = 0; i < Graph[curr].size(); i++) {
			int next = Graph[curr][i];
			if (next == to) return true;
			if (!Check[next]) {
				Check[next] = true;
				q.push(next);
			}
		}
		q.pop();
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie();

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int heavy, light;
		cin >> heavy >> light;
		Graph[heavy].push_back(light);
	}

	for (int i = 1; i <= N; i++) {
		int cnt = 0;
		for (int j = 1; j <= N; j++) {
			if (bfs(i, j) || bfs(j, i)) cnt++;
		}
		cout << N - cnt << endl;
	}
	return 0;
}
