// https://www.acmicpc.net/problem/1135

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 50;
int N;
vector<pair<int, int>> Graph[MAX];

int dfs(int p = 0) {
	int ret = 0, size = Graph[p].size();

	for (int i = 0; i < size; i++)
		Graph[p][i].first = 1 + dfs(Graph[p][i].second);

	// 시간이 큰 순서대로 정렬 (먼저 전화해야함)
	sort(Graph[p].rbegin(), Graph[p].rend());

	for (int i = 0; i < size; i++) {
		// n번째로 전화를 하면 총 전화 시간 + n을 더해야 전체 시간이 됨
		Graph[p][i].first += i;
		ret = max(ret, Graph[p][i].first);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int p;
		cin >> p;
		if (p == -1) continue;
		Graph[p].push_back({ 0, i });
	}
	cout << dfs()<< endl;
	return 0;
}
