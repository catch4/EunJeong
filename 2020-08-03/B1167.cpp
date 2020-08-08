// https://www.acmicpc.net/problem/1167

// DFS로 풀고, BFS로도 풀었다. (아래는 BFS)
// 주어지는 정점 번호가 무조건 순서대로 주어지는 것이 아닌가보다.
// 그거 때문에 틀렸습니다를 엄청 많이 받았다 ㅡㅡ

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, Leaf, Farthest;
vector<pair<int, int>> Tree[100001];
int Visited[100001];

void bfs(int node) {
	memset(Visited, -1, sizeof(Visited));

	queue<int> q;
	q.push(node);
	Visited[node] = 0;

	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		for (int i = 0; i < Tree[curr].size(); i++) {
			int next = Tree[curr][i].first;
			int dist = Tree[curr][i].second;
			if (Visited[next] == -1) {
				q.push(next);
				Visited[next] = Visited[curr] + dist;
				if (Farthest < Visited[next]) {
					Leaf = next;
					Farthest = Visited[next];
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		int curr, node;
		cin >> curr;
		while (cin >> node && 0 < node) {
			int dist;
			cin >> dist;
			Tree[curr].push_back({ node, dist });
		}
	}
	bfs(1);
	bfs(Leaf);
	cout << Farthest << endl;
	return 0;
}
