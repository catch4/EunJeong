// https://www.acmicpc.net/problem/2696
// 이게 왜 골드 3 이지...?

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		vector<int> v;
		int N;
		cin >> N;
		cout << N / 2 + 1 << endl;
		for (int i = 1; i <= N; i++) {
			int tmp;
			cin >> tmp;
			v.push_back(tmp);
			if (i & 1) {
				sort(v.begin(), v.end());
				cout << v[i / 2] << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
