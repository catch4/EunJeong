// https://www.acmicpc.net/problem/16235
// 처음에 나무들의 나이에 -를 붙여서 우선순위 큐를 사용했는데
// 큐를 복사하고 pop & push 하는 등 연산 때문인지 시간 초과가 발생했다.. ㅠ

// 처음에 입력으로 들어오는 나무는 하나 뿐이므로 시간이 지나도 나무의 나이의 순위는 변함이 없다.
// 따라서, 나이가 들어서 양분을 못 먹는 나무는 없애주고,
// 나이가 1인 새로 생긴 나무는 무조건 앞에 추가하면 매번 정렬을 하지 않아도 괜찮다!
// 즉, 우선순위 큐처럼 매번 정렬, pop & push, 복사 등의 과정 없이 구현할 수 있음을 알 수 있다.

// (1) vector로 sort하는 방법과 (2) deque를 사용하는 방법으로 풀었는데 둘 다 시간초과 없이 가능했다.
// 아래는 deque를 사용한 소스코드이다.

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 10;
const int dir[8][2] = { {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1} };
int N, M, K;
int Map[MAXN][MAXN];	// 땅애 남은 양분 (초기값 : 5)
deque<int> Trees[MAXN][MAXN];	// 해당 칸 나무의 나이 정보
int A[MAXN][MAXN];	// 겨울에 추가되는 양분 정보

bool in_range(int r, int c) {
	return 0 <= r && r < N && 0 <= c && c < N;
}

void init() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			Map[i][j] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		Trees[x - 1][y - 1].push_back(z);
	}
}

void oneYear() {
	// 봄: 나무가 자신의 나이만큼 양분을 먹고 나이 1 증가
	// 여름: 죽은 나무 각각 나이의 절반이 양분으로 추가
	// 가을: 나이가 5의 배수인 나무가 번식해서 인접한 8개의 칸에 나이 1인 나무 추가
	// 겨울: A[r][c]만큼 각 칸에 양분 추가

	// 가을만 빼면 각각의 과정이 독립적이므로 굳이 계속 맵 전체를 스캔할 필요는 없을 것 같았다.
	// 그냥 맵 전체를 스캔하면서 한번에 봄, 여름, 겨울 과정을 같이 해줬고,
	// 나무가 추가되는 가을은 따로 좌표만 저장해두고 나중에 나무 추가를 해줬다.

	vector<pair<int, int>> add;	// 나무 추가할 좌표
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 봄
			int k = 0;
			for (; k < Trees[i][j].size(); k++) {
				int& curr = Trees[i][j][k];
				if (curr <= Map[i][j]) {
					Map[i][j] -= curr;
					curr++;
					if (curr % 5 == 0)
						add.push_back({ i, j });
				}
				else break;
			}
			// 여름
			for (int l = Trees[i][j].size() - 1; k <= l; l--) {
				int curr = Trees[i][j][l];
				Map[i][j] += curr / 2;
				Trees[i][j].pop_back();
			}
			// 겨울
			Map[i][j] += A[i][j];
		}
	}

	// 가을
	for (int i = 0; i < add.size(); i++) {
		int x = add[i].first;
		int y = add[i].second;
		for (int d = 0; d < 8; d++) {
			int nx = x + dir[d][0];
			int ny = y + dir[d][1];
			if (in_range(nx, ny))
				Trees[nx][ny].push_front(1);
		}
	}
}

int Answer() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ret += Trees[i][j].size();
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	init();
	while (K--) {
		oneYear();
	}
	cout << Answer() << endl;
	return 0;
}
