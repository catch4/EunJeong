// https://www.acmicpc.net/problem/5719

// 다익스트라 - 도로 지우기 - 다익스트라로 하면 되겠다는 건 쉽게 생각했는데,
// 이걸 어떻게 구현해야 하는지 머리가 좀 아팠던 것 같다 ㅠㅠ
// 최단 경로가 여러 개일 때도 구해야하므로 거리가 같을 때도 고려를 해줘야 하는게 포인트.

// [1] 다익스트라를 이용해서 최단 거리가 되는 경로를 모두 구한다.
//     구한 경로들은 Path 배열에 to -> from으로 가는 (반대로 가는) 그래프가 되도록 만들어진다.
//     최단 경로 역추적을 할 때, 아무 경로가 하나만 필요하면 1차원 배열을 썼는데,
//     문제에서 최단 경로가 여러가지 경우의 수가 나올 수 있으므로 2차원 배열을 썼다.

// [2] Path 배열로 역추적을 해서 최단 경로에 포함되는 도로들의 거리를 -1로 바꿔줬다.
//     처음에 아무 생각없이 INF 값으로 바꿔줬는데,
//     다시 생각해보니 다익스트라를 한 번 더 돌릴 때 오버플로우가 날 것 같았다.

// [3] 최단 경로 도로가 지워진 상태에서 다익스트라를 한 번 더 돌려서 최단 경로를 찾는다.

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 500;
const int INF = 0x7FFFFFFF;

int N, M, S, D;
vector<pair<int, int>> Map[MAX];
vector<int> Path[MAX];	// 역추적을 할 때 필요한 배열
int Dist[MAX];	// Dist[i]: 시작 노드로부터 i까지의 거리
bool Visit[MAX][MAX];

void djikstra() {
	for (int i = 0; i < N; i++) Dist[i] = INF;

	priority_queue<pair<int, int>> q;
	q.push({ 0, S });
	Dist[S] = 0;

	while (!q.empty()) {
		int from = q.top().second;
		int currDist = -q.top().first;
		q.pop();
		
		// 이미 구한 거리가 더 짧으면 무시
		if (Dist[from] < currDist) continue;

		for (auto& next : Map[from]) {
			int to = next.first;
			int nextDist = currDist + next.second;

			if (next.second < 0) continue;	// 이미 지워진 도로
			if (nextDist > Dist[to]) continue;	// 이미 더 짧은 경로로 구했음

			if (nextDist < Dist[to]) {
				q.push({ -nextDist, to });
				Dist[to] = nextDist;
				Path[to].clear();	// 더 짧은 경로를 찾았으므로 기존의 최단 경로 배열은 지움
			}
			// 거리가 같더라도 경로 역추적 때 필요하므로 push 해야 함
			Path[to].push_back(from);
		}
	}
}

// 도착점(D)부터 BFS처럼 수행해서 도로를 지우는 함수
void erase_edge() {
	queue<int> q;
	q.push(D);

	while (!q.empty()) {
		int from = q.front();
		q.pop();

		for (auto& next : Path[from]) {
			int to = next;

			// Path는 반대로 들어있으므로 다시 Map에서 해당 간선을 찾음
			for (auto& node : Map[to]) {
				if (node.first == from)
					node.second = -1;
			}
			q.push(to);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	while (cin >> N >> M) {
		if (!(N && M)) break;
		memset(Visit, false, sizeof(Visit));
		for (int i = 0; i < N; i++) {
			Map[i].clear();
			Path[i].clear();
		}

		cin >> S >> D;
		int from, to, weight;
		for (int i = 0; i < M; i++) {
			cin >> from >> to >> weight;
			Map[from].push_back({ to, weight });
		}

		djikstra();
		erase_edge();
		djikstra();

		cout << (Dist[D] == INF ? -1 : Dist[D]) << endl;
	}
	return 0;
}
