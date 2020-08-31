// https://www.acmicpc.net/problem/13905

// 중량제한 문제가 생각났다.
// 이분탐색으로 무게를 미리 정하고, 다익스트라로 S에서 E로 도착할 수 있는지 검사했다.

// 푸는건 나름 수월하게 풀었는데 100% 까지 가서 틀렸습니다를 받았다.
// 이런 경우 주로 제일 작은 케이스일 때 틀리는 경우여서
// 2 1 / 1 2 / 1 2 1 로 테스트해보니 틀린 답이 나왔다... (맞는 답은 1인데 0이 나옴)
// 이분탐색을 뭔가 이상하게 해서 그런거였고, 고치니까 AC를 받았다.

// 고려 & 수정한 점
// [1] 다익스트라에서 dist 값이 int의 범위를 넘는다. => long long으로 변경
// [2] 처음에 INF의 값을 최댓값과 같게 하면 안된다. (INF와 비교하기 때문) => INF에 +1
// [3] while(left < right)로 하면 left = 1, right = 1인 경우에 아예 검사를 안하고
//	   바로 0을 뱉아서 틀렸다. (100%까지 가서 틀린 이유^.^) => while(left <= right)로

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define endl '\n';
typedef long long ll;
using namespace std;

const ll INF = (ll)1000000 * 300000 + 1;
int N, M, S, E;
vector<pair<int, ll>> Island[100001];
ll dist[100001];

// 다익스트라로 w 이상의 도로만 써서 S에서 E까지 갈 수 있는지 검사
bool findWay(ll w) {
	for (int i = 0; i <= N; i++) dist[i] = INF;
	dist[S] = 0;

	priority_queue<pair<ll, int>> q;
	q.push({ 0, S });

	while (!q.empty()) {
		int currHouse = q.top().second;
		ll currCost = -q.top().first;
		q.pop();

		if (dist[currHouse] < currCost) continue;

		for (auto next : Island[currHouse]) {
			int nextHouse = next.first;
			ll nextCost = next.second;
			// 도로가 w 이상일 때만 갈 수 있다.
			if (w <= next.second && currCost + nextCost <= dist[nextHouse]) {
				dist[nextHouse] = currCost + nextCost;
				q.push({ -dist[nextHouse], nextHouse });
			}
		}
	}
	if (dist[E] == INF) return false;
	else return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> S >> E;
	ll left = 1, right = 0;
	for (int i = 0; i < M; i++) {
		int from, to; ll weight;
		cin >> from >> to >> weight;
		Island[from].push_back({ to, weight });
		Island[to].push_back({ from, weight });
		if (right < weight) right = weight;
	}
	// 이분탐색
	ll mid = 0, answer = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (findWay(mid)) {	// 길이 있는 경우
			answer = mid ;	// answer 값 갱신
			left = mid + 1;
		}
		else right = mid - 1;
	}
	cout << answer << endl;
	return 0;
}
