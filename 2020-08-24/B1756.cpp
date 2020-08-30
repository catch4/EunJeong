// https://www.acmicpc.net/problem/1756

// 오븐의 지름을 입력받을 때, 뒤에 나오는 큰 지름은 신경 쓸 필요가 없다.
// ex) 5 6 4 3 6 2 3 -> 5 5 4 3 3 2 2 로 바꿔도 무방
// 처음에 피자 반죽이 들어가는 위치를 찾는걸 이분 탐색으로 풀었는데 계속 틀렸다 ㅎㅎ;
// 63%까지 올라가다가 틀렸습니다 나오는거 보니까 답이 0인 경우에 대해 제대로 처리를 안 해준 것 같았다.
// 그래서 그냥 다 갈아엎고 오븐의 제일 아래부터 입력으로 들어오는 피자 반죽의 크기랑 비교해서 pos를 감소시켰다.

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 300001;
const int INF = 0x7FFFFFFF;
int D, N;
int Oven[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> D >> N;
	int min_oven = INF;
	for (int i = 1; i <= D; i++) {
		int r;
		cin >> r;
		Oven[i] = min_oven = min(r, min_oven);
	}
	int dough, pos = D + 1;
	for (int i = 0; i < N; i++) {
		cin >> dough;
		if (pos <= 0) continue;
		pos--;
		while (Oven[pos] < dough && 0 < pos) { pos--; }
	}
	cout << pos << endl;
	return 0;
}
