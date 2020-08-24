#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define endl '/n'

using namespace std;
const int MAX = 51;

int N, M;
vector<int> Parties[MAX];
bool truth[MAX], Participate[MAX][MAX], truthParth[MAX];

void solve() {
	queue<int> q;

	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;

		for (int j = 0; j < num; j++) {
			int idx;
			cin >> idx;

			Participate[i][idx] = true;

			if (truth[idx] && !truthParth[i]) {
				truthParth[i] = true;
				q.push(i);
			}

			for (int k = 0; k < i; k++) {
				bool isParticipated = Participate[k][idx];

				if (isParticipated) {
					Parties[k].push_back(i);
					Parties[i].push_back(k);
				}
			}
		}
	}

	while (!q.empty()) {
		int idx = q.front();
		q.pop();

		for (int i = 0; i < Parties[idx].size(); i++) {
			int party = Parties[idx][i];

			if (truthParth[party] == false) {
				truthParth[party] = true;
				q.push(party);
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;

	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int idx;
		cin >> idx;

		truth[idx]++;
	}
	
	solve();

	int answer = 0;
	for (int i = 0; i < M; i++) {
		if (truthParth[i] == false) {
			answer++;
		}
	}

	cout << answer << endl;

	return 0;
}
