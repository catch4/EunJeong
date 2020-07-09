// https://www.acmicpc.net/problem/1939

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, Start, End;
vector<pair<int, int>> Graph[10001];
bool Visit[10001];

bool bfs(int weight) {
	if (Start == End)
        return true;
    
	for (int i = 1; i <= N; i++)
		Visit[i] = false;

	queue<int> q;
	q.push(Start);
	Visit[Start] = true;

	while (!q.empty()) {
		int curr = q.front();
		for (int i = 0; i < Graph[curr].size(); i++) {
			int next = Graph[curr][i].first;
			int nextWeight = Graph[curr][i].second;
			if (!Visit[next] && weight <= nextWeight) {
				if (next == End)
                    return true;
				Visit[next] = true;
				q.push(next);
			}
		}
		q.pop();
	}
	return false;
}

int main() {
	cin >> N >> M;
	int left = 0x7FFFFFFF, right = 0;
	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		Graph[x].push_back({ y, z });
		Graph[y].push_back({ x, z });
		if (z < left) left = z;
		if (right < z) right = z;
	}
	cin >> Start >> End;

	for (int i = 1; i <= N; i++) {
		sort(Graph[i].begin(), Graph[i].end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.second > b.second;
		});
	}

	while (left <= right) {
		int mid = (left + right) / 2;
		if (bfs(mid)) left = mid + 1;
		else right = mid - 1;
	}
	cout << right << endl;
	return 0;
}
