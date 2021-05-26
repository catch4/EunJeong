// https://www.acmicpc.net/problem/17352

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 300000;
int N;
vector<int> Islands[MAX+1];
bool Visited[MAX+1];

void bfs(int x = 0) {
    queue<int> q;
    q.push(x);
    Visited[x] = true;

    while(!q.empty()) {
        int cx = q.front();
        for (auto nx : Island[cx]) {
            if (Visited[nx]) continue;
            q.push(nx);
            Visited[nx] = true;
        }
        q.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 0; i < N - 2; ++i) {
        int from, to;
        cin >> from >> to;
        --from, --to;
        Islands[from].push_back(to);
        Islands[to].push_back(from);
    }

    bfs();
    for (int i = 0; i < N; ++i) {
        if (Visited[i]) {
            cout << i + 1 << ' ';
            break;
        }
    }
    for (int i = 0; i < N; ++i) {
        if (!Visited[i]) {
            cout << i + 1;
            break;
        }
    }

    return 0;
}
