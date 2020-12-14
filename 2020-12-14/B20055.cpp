// https://www.acmicpc.net/problem/20055

#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int N, K;
int D[202];
vector<int> Robot;

bool is_done() {
	int count = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (D[i] == 0) count++;
		if (K <= count) return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++) {
		cin >> D[i];
	}
	
	int pos = 0, answer = 0;
	while (!is_done()) {
		answer++;

		//1. 한 칸 회전
		pos--;
		if (pos < 0) pos = (2 * N) - 1;

		// 2. 로봇 이동
		vector<int> tmp;
		for (int i = 0; i < Robot.size(); i++) {
			int curr = Robot[i];
			int next = (curr + 1) % (2 * N);

			// 내려가는 위치
			if (curr == ((pos + N) % (2 * N)) || next == ((pos + N) % (2 * N)))
				continue;

			// 앞 칸의 내구도가 0이거나 로봇이 있는 경우 => 이동 불가능
			if (!D[next] || (!tmp.empty() && tmp.back() == next)) {
				tmp.push_back(curr);
				continue;
			}

			// 그 외의 경우는 한 칸 이동하고 내구도 감소
			tmp.push_back(next);
			D[next]--;
		}
		Robot = tmp;

		// 3. 제일 앞 칸의 내구도가 1 이상이고 로봇이 없으면 올리기
		if (0 < D[pos] && (Robot.empty() || Robot.back() != pos)) {
			D[pos]--;
			Robot.push_back(pos);
		}
	}
	cout << answer << endl;
	return 0;
}
