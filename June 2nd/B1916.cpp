// https://www.acmicpc.net/problem/1916
// 음수가 없는 가중치 그래프의 최소 비용 -> 다익스트라
// 시간복잡도를 더 줄일 수 있는 우선순위 큐를 이용해 다익스트라 구현

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 0x7FFFFFFF;
int N, M, Start, End;
vector<pair<int, int>> Adj[1001];	// 인접 리스트. <연결된 정점, 거리>

int djikstra(int start = Start, int end = End) {
	vector<int> dist(N + 1, INF);	 // start 정점으로부터의 거리 최솟값(INF로 초기화)
	dist[start] = 0;
	priority_queue<pair<int, int>> pq;	// 우선순위 큐 <-거리, 정점> : 거리가 작은 것부터 정렬하기 위해 음수값을 넣어준다
	pq.push({ 0, start });

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int from = pq.top().second;
		pq.pop();

		if (dist[from] < cost) continue;	// 이미 더 짧은 경로라면 무시
		// 인접한 정점 검사
		for (int i = 0; i < Adj[from].size(); i++) {
			int to = Adj[from][i].first;
			int nextDist = cost + Adj[from][i].second;
			if (dist[to] > nextDist) {	// 계산한 거리값이 dist[to]보다 작은 경우만 큐에 넣는다
				dist[to] = nextDist;
				pq.push({ -nextDist, to });
			}
		}
	}
	return dist[end];
}

int main() {
	// 입력량 많음
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		Adj[v1].push_back({ v2, w });
	}
	cin >> Start >> End;
	cout << djikstra() << endl;
	return 0;
}
