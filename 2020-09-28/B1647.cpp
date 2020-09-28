#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct kruskal {
	int from;
	int to;
	int cost;
} node;

vector<node> Graph;
int Parent[100002];
int Answer;
bool Check;

bool cmp(node d1, node d2) {
	return d1.cost < d2.cost;
}

int find(int u) {
	if (u == Parent[u])
		return u;

	return Parent[u] = find(Parent[u]);
}

void merge(int u, int v) {
	Check = false;
	u = find(u);
	v = find(v);

	if (u == v) return;

	Parent[u] = v;
	Check = true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; i++) Parent[i] = i;

	for (int i = 0; i < M; i++) {
		node n;
		cin >> n.from >> n.to >> n.cost;
		Graph.push_back(n);
	}
	sort(Graph.begin(), Graph.end(), cmp);

	int max_edge = 0;
	for (int i = 0; i < M; i++) {
		merge(Graph[i].from, Graph[i].to);

		if (Check) {
			Answer += Graph[i].cost;
			if (max_edge < Graph[i].cost) max_edge = Graph[i].cost;
		}
	}

	cout << Answer - max_edge << endl;

	return 0;
}
