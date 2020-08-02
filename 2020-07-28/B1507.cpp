// https://www.acmicpc.net/problem/1507

// 이렇게 푸는거 맞나 싶어서 검색해봤는데 간단한 방법이 있었다. 진짜 이상하게 푼 것 같다 ㅋㅋㅋ;
// 딱히 방법이 떠오르지 않아서 플로이드 와샬 알고리즘의 최단거리 역추적을 이용했다.

// 1. DP값이 같으면 해당 부분은 거쳐가는게 빠르다는 거니까 직전 노드를 바꿔주고
// 2. 마지막에 직전 노드값으로 경로를 역추적하면서 중복되지 않게 체크하면서 더해줬다.
// 처음에 불가능한 경우 -1을 출력하는 것을 보지 않아서 "틀렸습니다"에 멘탈이 터질 뻔했는데..^^
// 3. 어떤 도시를 거쳐가는 것보다 해당 경로가 짧은게 불가능한 경우였다.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int N, Answer;
int DP[21][21];
int Path[21][21];
bool Check[21][21];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> DP[i][j];
			Path[i][j] = i;
		}
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == k) continue;
        // 3.
				if (DP[i][j] > DP[i][k] + DP[k][j]) {
					cout << "-1" << endl;
					return 0;
				}
        // 1.
				if (DP[i][j] == DP[i][k] + DP[k][j]) {
					Path[i][j] = Path[k][j];
				}
			}
		}
	}
  // 2.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			stack<int> s;
			int prev = j;
			s.push(prev);

			while (i != prev) {
				prev = Path[i][prev];
				s.push(prev);
			}

			int curr = i;
			while (!s.empty()) {
				int next = s.top();
				if (!Check[curr][next]) {
					Check[curr][next] = Check[next][curr] = true;
					Answer += DP[curr][next];
				}
				curr = next;
				s.pop();
			}
		}
	}
	cout << Answer << endl;
	return 0;
}
