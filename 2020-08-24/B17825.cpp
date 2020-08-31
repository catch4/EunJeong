// https://www.acmicpc.net/problem/17825

#include<iostream>
using namespace std;

int Dice[10];	// 주사위
int Piece[4];	// 말

int Map[35];	// 윷놀이 판
int Score[35];	// 추가되는 점수
int Turn[35];	// 방향 전환
bool Check[35];	// 말 있는지 확인

int Answer = 0;

void dfs(int cnt, int sum) {
	if (cnt == 10) {
		if (sum > Answer)
			Answer = sum;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int prev = Piece[i];
		int now = prev;
		// 움직여야 하는 횟수
		int move = Dice[cnt];

		// 방향 전환 해야하는 곳이면 방향 전환
		if (Turn[now]) {
			now = Turn[now];
			move -= 1;
		}

		// 주사위 만큼 이동
		while (move--) {
			now = Map[now];
		}

		// 21(도착점)이 아니고 이미 말이 있으면 통과
		if (now != 21 && Check[now]) continue;

		Check[prev] = false;
		Check[now] = true;
		Piece[i] = now;

		dfs(cnt + 1, sum + Score[now]);

		Piece[i] = prev;
		Check[prev] = true;
		Check[now] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	// 맵 만들기 (다음 노드를 가리킴)
	for (int i = 0; i < 32; i++)
		Map[i] = i + 1;
	Map[21] = 21; Map[30] = 25; Map[32] = 25; Map[27] = 20;

	// 방향 전환 하는 파란색 칸
	Turn[5] = 22; Turn[10] = 31; Turn[15] = 28;
	Turn[25] = 26;

	// 점수판 만들기
	for (int i = 0; i < 21; i++) Score[i] = i * 2;
	Score[22] = 13; Score[23] = 16; Score[24] = 19;
	Score[31] = 22; Score[32] = 24; Score[28] = 28;
	Score[29] = 27; Score[30] = 26; Score[25] = 25;
	Score[26] = 30; Score[27] = 35;

	// 주사위 입력 받기
	for (int i = 0; i < 10; i++)
		cin >> Dice[i];

	dfs(0, 0);

	cout << Answer << endl;
	return 0;
}
