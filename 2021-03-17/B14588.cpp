// https://www.acmicpc.net/problem/14588

// 자기 자신과의 거리는 0, 인접한 선분과의 거리는 1로 두고 플로이드 와샬을 씀

#include <iostream>
#define endl '\n'
using namespace std;

const int MAX = 300;
const int INF = 987654321;
int N, Q;
struct Line {
	int left, right;
} Lines[301];
int D[MAX + 1][MAX + 1];

bool is_overlapped(const Line& u, const Line& v) {
	if ((u.left <= v.left && u.right >= v.right)
		|| (v.left <= u.left && v.right >= u.right)
		|| (v.left <= u.right && u.left <= v.right)
		|| (u.left <= v.right && v.left <= u.right)) return true;
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int l, r;
		cin >> l >> r;
		Lines[i] = { l, r };
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			D[i][j] = INF;
			if (i == j) D[i][j] = 0;
			else if (is_overlapped(Lines[i], Lines[j])) D[i][j] = 1;
		}
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		cout << (D[l][r] == INF ? -1 : D[l][r]) << endl;
	}
	return 0;
}
