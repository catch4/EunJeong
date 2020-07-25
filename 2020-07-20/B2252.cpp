// https://www.acmicpc.net/problem/2252

// 위상정렬 문제
// 방향 그래프와 카운트, 체크 배열을 두고
// 카운트가 0인 노드부터 출력해줬다.

#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> Students[32002];
int Count[32002];
bool Check[32002];

// 모든 노드가 체크되었는지 확인하는 함수
bool isDone() {
	for (int i = 1; i <= N; i++) {
		if (!Check[i]) return false;
	}
	return true;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int s, t;
		cin >> s >> t;
		Students[s].push_back(t);
		Count[t]++;	// 선행되어야할 노드가 몇 개 있는지
	}
	do {
		for (int i = 1; i <= N; i++) {
			if (!Check[i] && !Count[i]) {	// 카운트가 0이면 출력해도 됨
				Check[i] = true;
				cout << i << " ";
				for (int j = 0; j < Students[i].size(); j++) {
					Count[Students[i][j]]--;	// 연결된 노드의 카운트 빼주기
				}
			}
		}
	} while (!isDone());
	cout << endl;
	return 0;
}
