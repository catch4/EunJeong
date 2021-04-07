#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5;
const int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
char Seats[5][5];
bool Checked[5][5];
vector<pair<int, int>> Group;
unordered_set<string> Groups;

string make_hash(vector<pair<int, int>>& vec) {
    string ret = "";
    for (auto v : vec) {
        ret += to_string(v.first);
        ret += to_string(v.second);
    }
    return ret;
}

bool in_range(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void grouping(int s, int n = 1) {
    if (n == 7) {
        if (s < 4) return;
        vector<pair<int, int>> tmp = Group;
        sort(tmp.begin(), tmp.end());
        string hash = make_hash(tmp);
        if (Groups.find(hash) != Groups.end()) return;
        Groups.insert(hash);
        return;
    }
    for (auto v : Group) {
        for (int d = 0; d < 4; d++) {
            int nx = v.first + dir[d][0];
            int ny = v.second + dir[d][1];

            if (!in_range(nx, ny)) continue;
            if (Checked[nx][ny]) continue;

            Group.push_back({nx, ny});
            Checked[nx][ny] = true;
            grouping(Seats[nx][ny] == 'S' ? s + 1 : s, n + 1);
            Checked[nx][ny] = false;
            Group.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> Seats[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Group.push_back({i, j});
            Checked[i][j] = true;
            grouping(Seats[i][j] == 'S' ? 1 : 0);
            Group.clear();
            memset(Checked, false, sizeof(Checked));
        }
    }
    cout << Groups.size() << endl;
    return 0;
}
