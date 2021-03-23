// https://www.acmicpc.net/problem/20366

// '크지 않은'인데 같은 경우까지 제외해버려서 몇 번 틀림...ㅎ
// 오름차순으로 정렬해둬서 바로 break; 해버리니까 시간초과 안 걸림.

#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

struct Snowman {
	int height, a, b;
};
int N, Answer = 0x7FFFFFFF;
int R[601];
vector<Snowman> Snowmans;

bool cmp(const Snowman& u, const Snowman& v) {
	return u.height < v.height;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> R[i];
	}
	sort(R, R + N);
	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			Snowmans.push_back({ R[i] + R[j], i, j });
		}
	}
	sort(Snowmans.begin(), Snowmans.end(), cmp);

	for (int i = 0; i < Snowmans.size() - 1; ++i) {
		for (int j = i + 1; j < Snowmans.size(); ++j) {
			auto elsa = Snowmans[i], anna = Snowmans[j];
			if (elsa.a == anna.a || elsa.b == anna.b || elsa.a == anna.b || elsa.b == anna.a) continue;
			Answer = min(Answer, abs(elsa.height - anna.height));
			break;
		}
	}

	cout << Answer << endl;
	return 0;
}
