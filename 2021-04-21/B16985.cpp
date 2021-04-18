// https://www.acmicpc.net/problem/16985

// 판 다 미리 회전 시키기 => 각각 회전된 경우 뽑기 => 5개 순열 돌리기
// 뭔가 중복?되는 경우가 생겨서 시간초과 될 것 같아서
// 일단 대충 짜고 최적화하려고 했는데 잉? 그냥 통과됐다 ㅎ N이 작아서 그런가보다.
// 처음에는 판 쌓는 순서도 바꿀 수 있는거 몰라서 틀렸고
// 그 다음에는 54번째 줄 안해줘서 틀렸다 ㅎ 귀찮아도 예제는 돌려보자~~

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
const int N = 5;
const int MAX = 0x7FFFFFFF;
const int dir[6][3] = { { 0, 0, -1 }, {0, -1, 0}, {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, 0, 1} };

vector<vvi> Board[5];
vector<vvi> SelectedBoard(5);
vector<vvi> Maze;
int Visit[N][N][N], Check[N];
int Answer = MAX;
struct Point {
    int x, y, z;
};

bool in_range(int x, int y, int z) {
    return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

// Board의 들어있는 5개의 판을 각각 회전시켜서 미리 넣어두기
void rotate() {
    for (int i = 0; i < 5; i++) {
        vvi arr(N, vi(N));
        arr = Board[i][0];
        for (int j = 0; j < 3; j++) {
            vvi tmp(N, vi(N));
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 5; b++) {
                    tmp[a][b] = arr[b][N - a - 1];
                }
            }
            Board[i].push_back(tmp);
            arr = tmp;
        }
    }
}

// 만들어진 미로에서 BFS로 가장 짧은 거리 구하기
int shortest_way() {
    if (!Maze[0][0][0]) return -1;
    queue<Point> q;
    q.push((Point){0, 0, 0});
    Visit[0][0][0] = 1;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int z = q.front().z;

        for (int d = 0; d < 6; d++) {
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];
            int nz = z + dir[d][2];

            if (!in_range(nx, ny, nz)) continue;
            if (!Maze[nx][ny][nz]) continue;
            if (Visit[nx][ny][nz]) continue;
            q.push((Point){nx, ny, nz});
            Visit[nx][ny][nz] = Visit[x][y][z] + 1;
        }
        q.pop();
    }
    return Visit[N - 1][N - 1][N - 1] - 1;
}

// 선택된 5개의 판을 조합해서 미로 만들기
void make_maze(int n = 0) {
    if (n == 5) {
        memset(Visit, 0, sizeof(Visit));
        int count = shortest_way();
        if (count != -1 && count < Answer) {
            Answer = count;
        }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (Check[i]) continue;
        Check[i] = true;
        Maze.push_back(SelectedBoard[i]);
        make_maze(n + 1);
        Maze.pop_back();
        Check[i] = false;
    }
}

// 0 ~ 4번판 순서대로 얼마나 회전할 건지 정하기
void solve(int n = 0) {
    if (n == 5) {
        memset(Check, 0, sizeof(Check));
        make_maze();
        return;
    }
    for (int i = 0; i < 4; i++) {
        SelectedBoard[n] = Board[n][i];
        solve(n + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    for (int k = 0; k < 5; k++) {
        vvi tmp(N, vi(N));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> tmp[i][j];
            }
        }
        Board[k].push_back(tmp);
    }
    rotate();
    solve();
    if (Answer == MAX) cout << -1;
    else cout << Answer;

    return 0;
}
