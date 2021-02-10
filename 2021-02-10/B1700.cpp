// https://www.acmicpc.net/problem/1700

// 그냥 DFS로 풀면 당연히 시간 초과날 것 같았는데 진짜 시간 초과 ^.^
// 콘센트를 뽑을 때 앞으로 안 쓸 콘센트나 오랫동안 안 쓸 콘센트를 빼면 된다.
// dfs 재귀 형식으로 출발해서 함수로 만들어져 있는데 다 짜고 보니까 그냥 while 문으로 짜면 되겠구나...

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K, Answer;
vector<int> Elec;
vector<int> Plug;

void solve(int curr = 0, int cnt = 0) {
    if (curr == K) {
        Answer = cnt;
        return;
    }

    // 콘센트에 이미 꽂혀 있는지 찾아본다.
    if (find(Plug.begin(), Plug.end(), Elec[curr]) != Plug.end()) {
        // 이미 꽂혀있으면 카운트 증가 X, 다음으로 이동
        solve(curr + 1, cnt);
    }
    // 꽂혀있지 않으면 
    else {
        // 자리가 남아있으면 바로 꽂으면 된다.
        if (Plug.size() < N) {
            Plug.push_back(Elec[curr]);
            solve(curr + 1, cnt);
        }
        // 아니면 뺄 콘센트를 찾아야 한다.
        // 가장 오랫동안 안 쓰거나 앞으로 안 쓰는 콘센트를 뽑는다.
        else {
            int idx = 0, iidx = 0;
            // 현재 콘센트에 끼워져 있는 플러그를 다 검사해본다.
            for (int i = 0; i < Plug.size(); i++) {
                int ii = 0;
                // 앞으로 꽂을 플러그들을 쭉 보면서
                for (int j = curr + 1; j < Elec.size(); j++) {
                    if (Elec[j] == Plug[i]) break;
                    ii++;
                }
                // 제일 큰(나중에 쓸) 값을 저장해두고
                if (iidx < ii) {
                    idx = i;
                    iidx = ii;
                }
            }
            // 플러그를 교체한다.
            Plug[idx] = Elec[curr];
            solve(curr + 1, cnt + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int e;
        cin >> e;
        Elec.push_back(e);
    }
    solve();
    cout << Answer << endl;
    return 0;
}
