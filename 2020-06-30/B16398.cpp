// https://www.acmicpc.net/problem/16398
// 처음에 queue + BFS로 풀었는데 시간초과가 났다..
// 다른 해결책을 모르겠어서 찾아보니 Union-find였다 ㅠ_ㅠ
// Union-find 다시 공부해야 할 듯...

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000;
int planet[MAX][MAX];
int parent[MAX], ranks[MAX];

// Union Find.
int findParent(int v) {
	if (v == parent[v]) return v;
	return parent[v] = findParent(parent[v]);
}

void merge(int a, int b) {
	a = findParent(a);
	b = findParent(b);

	if (a != b) {
		if (ranks[a] < ranks[b])
			swap(a, b);

		parent[b] = a;
		
		if (ranks[a] == ranks[b])
			ranks[a]++;
	}
}

struct Edge {
	int u, v, weight;
	bool operator<(Edge const &e) {
		return weight < e.weight;
	}
};


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> planet[i][j];
		}
	}

	vector<Edge> edge;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			edge.push_back({ i, j, planet[i][j] });
		}
	}

	sort(edge.begin(), edge.end());

	for (int i = 0; i < N; i++) {
		parent[i] = i;
		ranks[i] = 0;
	}

	long long result = 0;

	for (int i = 0; i < edge.size(); i++) {
		Edge e = edge[i];
		if (findParent(e.u) != findParent(e.v)) {
			result += e.weight;
			merge(e.u, e.v);
		}
	}

	cout << result << "\n";
	return 0;
}
