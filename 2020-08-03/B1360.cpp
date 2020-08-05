// https://www.acmicpc.net/problem/1360

// 처음에 undo도 undo가 된다는 걸 안 보고 stack으로 풀어서 틀렸다 ㅠ
// 그 다음에 vector로 짰는데도 계속 틀리길래 뭐지?! 싶었는데
// 두번째 변수를 char 형으로 둬서 문제가 생긴거였다...
// type에서는 문제가 없지만 undo에서는 한 자리가 아니기 때문에 (최대 10^9)
// char 형식으로 받으면 안 됐는데 멍청했다 ㅎ_ㅎ 에효

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;
vector<pair<string, int>> V;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		string cmd, c; int time;
		cin >> cmd >> c >> time;
		if (cmd == "type") {
			string str = "";
			if (V.size()) str = V.back().first;
			V.push_back({ str + c, time });
		}
		else if (cmd == "undo") {
			int tg = time - atoi(c.c_str());
			string str = "";
			for (int id = V.size() - 1; 0 <= id; id--) {
				if (V[id].second < tg) {
					str = V[id].first;
					break;
				}
			}
			V.push_back({ str, time });
		}
	}
	cout << V.back().first << endl;
	return 0;
}
