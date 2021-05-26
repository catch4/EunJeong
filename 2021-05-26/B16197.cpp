// https://www.acmicpc.net/problem/16197

// 처음에 생각을 잘못해서 이상하게 품 ㅎㅎ;
// N, M이 20으로 작아서 시간 초과는 안 나는데 특정 위치를 계속 반복해서 시간이 오래 걸림
// cnt가 i일 때 동전 x, y의 위치를 기억해서 visit 확인을 하면 더 짧게 걸릴 것

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 20;
const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const char COIN = 'o';
const char EMPTY = '.';
const char WALL = '#';
const char OUT = 'x';

int N, M, Answer;
char Board[MAX + 2][MAX + 2];
struct pos {
    int x;
    int y;
};
vector<pos> Coin;

bool is_overlapped(vector<pos>& coin) {
    pos u = coin[0];
    pos v = coin[1];
    return (u.x == v.x && u.y == v.y);
}

bool is_both_out(vector<pos>& coin) {
    int fx = coin[0].x, fy = coin[0].y;
    int sx = coin[1].x, sy = coin[1].y;
    return Board[fx][fy] == OUT && Board[sx][sy] == OUT;
}

bool is_done (vector<pos>& coin) {
    for (int i = 0; i < coin.size(); i++) {
        int x = coin[i].x, y = coin[i].y;
        if (Board[x][y] == OUT) return true;
    }
    return false;
}

void play(int cnt = 0, vector<pos> coin = Coin) {
    if (cnt > 10 || is_overlapped(coin) || is_both_out(coin)) {
        Answer = Answer ? Answer : -1;
        return;
    }
    if (is_done(coin)) {
        if (Answer == 0 || Answer == -1) Answer = cnt;
        else Answer = Answer < cnt ? Answer : cnt;
        return;
    }
    for (int d = 0; d < 4; d++) {
        vector<pos> tmpCoin;

        pos firstCoin = (pos){coin[0].x + DIR[d][0], coin[0].y + DIR[d][1]};
        pos secondCoin = (pos){coin[1].x + DIR[d][0], coin[1].y + DIR[d][1]};

        tmpCoin.push_back(firstCoin);
        tmpCoin.push_back(secondCoin);

        for (int i = 0; i < tmpCoin.size(); i++) {
            int x = tmpCoin[i].x;
            int y = tmpCoin[i].y;
            if (Board[x][y] == WALL)
                tmpCoin[i] = coin[i];
        }
        play(cnt + 1, tmpCoin);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i <= N + 1; i++) Board[i][0] = Board[i][M + 1] = OUT;
    for (int i = 0; i <= M + 1; i++) Board[0][i] = Board[N + 1][i] = OUT;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> Board[i][j];
            if (Board[i][j] == COIN) {
                Coin.push_back((pos){i, j});
                Board[i][j] = EMPTY;
            }
        }
    }

    play();
    cout << Answer;
    return 0;
}
