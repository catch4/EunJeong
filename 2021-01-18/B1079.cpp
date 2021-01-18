// https://www.acmicpc.net/problem/1079

// 하.. 문제를 잘못 이해해서 삽질 겁나 했다 ㅡㅡ..
// 문제에서 마피아가 죽일 사람 한 명을 고른다고 해서 그냥 "고르기"만 하는 줄 알았는데
// 실제로 고른 사람을 "죽이고" 유죄지수를 반영시켜야 하는 거였다... (53번째 줄)

#include <iostream>
#include <cstring>
#define DEAD -987654321
using namespace std;

int N, EJ, Answer;
int GP[16], R[16][16];
bool Dead[16];

// 1) 밤에 마피아가 죽일 사람을 한 명 고른다.
// 2) 참가자 i가 죽었다면 다른 플레이어 j의 유죄지수가 R[i][j]만큼 바뀐다.
// 3) 낮에는 유죄지수가 가장 높은 사람이 죽는다. 같다면 번호가 작은 사람.

void play(int player = N, int day = 0) {
	if (Dead[EJ] || player == 1) {
		if (Answer < day) Answer = day;
		return;
	}

	// 낮.
	// 가장 죄가 있을 것 같은 한 명을 죽인다.
	if (player % 2) {
		int gp = 0, idx = 0;
		for (int i = 0; i < N; i++) {
			if (gp < GP[i] && !Dead[i]) {
				gp = GP[i];
				idx = i;
			}
		}
		if (idx == EJ) {
			if (Answer < day)
				Answer = day;
			return;
		}
		Dead[idx] = true;
		play(player - 1, day);
		Dead[idx] = false;
	}
	// 밤.
	// 마피아가 죽일 사람을 한 명 고른다.
	else {
		int tmpGP[16] = { 0, };
		memcpy(tmpGP, GP, sizeof(GP));

		for (int i = 0; i < N; i++) {
			if (i == EJ || Dead[i]) continue;
			Dead[i] = true;	// 여기서 고른 사람을 안 죽여서 계속 틀림
			for (int j = 0; j < N; j++) {
				if (Dead[j]) continue;
				GP[j] += R[i][j];
			}
			play(player - 1, day + 1);
			memcpy(GP, tmpGP, sizeof(GP));
			Dead[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> GP[i];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> R[i][j];
	cin >> EJ;
	play();
	cout << Answer << endl;
	return 0;
}
