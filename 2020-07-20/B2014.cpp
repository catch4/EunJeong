// https://www.acmicpc.net/problem/2014

// 처음 코드가 85% 정도에서 틀렸습니다가 나오는데
// 해결이 안 돼서 결국 또 그냥 검색을 해봤다^^..
// 다 비슷한데 자질구레한 조건들 때문에 틀린 것 같다.

#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>

#define ll long long
using namespace std;

int K, N;
ll Primes[102];
priority_queue<ll, vector<ll>, greater<ll>> PQ; // minHeap
unordered_map<ll, bool> Visited;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> Primes[i];
	}
	PQ.push(1);

	ll maxVal = 0;
	int cnt = 0;
	while (N--) {
		ll curr = PQ.top();
		PQ.pop();
		cnt++;

		for (int i = 0; i < K; i++) {
			ll next = curr * Primes[i];

			// N를 넘어간 개수가 들어있는데 현재 최댓값보다 큰 값이 들어오면 필요 없음
			if (N < PQ.size() && maxVal < next) continue;

			// 이미 큐에 존재하는 것은 넣지 않기 위해 중복 체크
			if (!Visited[next]) {
				Visited[next] = true;
				maxVal = max(maxVal, next);
				PQ.push(next);
			}
		}
	}
	cout << PQ.top() << endl;
	return 0;
}
