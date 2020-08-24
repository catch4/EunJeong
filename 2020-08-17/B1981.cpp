// https://www.acmicpc.net/problem/1981

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define endl '/n'
using namespace std;

const int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
int N, minValue = 500, maxValue = 0;
int Arr[102][102];
bool Check[102][102];

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < N;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Arr[i][j];
			minValue = min(minValue, Arr[i][j]);
			maxValue = max(maxValue, Arr[i][j]);
		}

		int start = 0, end = 200;
		int answer = 500;

		while (start <= end) {
			int mid = (start + end) / 2;

			bool in = false, out = false;
			for (int base = minValue; base + mid <= maxValue; base++) {
				in = true;
				if (out) break;

				memset(Check, 0, sizeof(Check));

				if (Arr[0][0] < base || Arr[0][0] > base + mid)
					continue;

				queue<pair<int, int>> q;
				q.push({ 0,0 });

				while (!q.empty()) {
					int y = q.front().first;
					int x = q.front().second;
					q.pop();

					if (Check[y][x]) continue;
					Check[y][x] = true;

					for (int i = 0; i < 4; i++) {
						int ny = dir[i][0] + y;
						int nx = dir[i][1] + x;

						if (in_range(ny, nx) && !Check[ny][nx]) {
							if (Arr[ny][nx] < base || Arr[ny][nx] > base + mid)
								continue;

							q.push({ ny,nx });
							if (ny == N - 1 && nx == N - 1)
								out = true;
						}
					}
				}
			}

			if (!in || out) {
				answer = min(mid, answer);
				end = mid - 1;
			}
			else start = mid + 1;
		}

		cout << answer << endl;
		return 0;
	}
