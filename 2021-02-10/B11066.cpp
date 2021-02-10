// https://www.acmicpc.net/problem/11066

// 처음에 파일이 인접해야 하는 줄 모르고 정렬하고 뻘짓하다가 시간 다 날림; ㅎ
// 중간 나누는 곳이 i로 뒀을 때 구간 [a, b]의 최솟값은
// min(구간 [a, i]의 최솟값) + 구간 [i + 1, b]의 최솟값)인 점을 이용

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int K, Answer;
int File[500];
int DP[501][501];
int Sum[501];

int answer(int s = 1, int e = K) {
    int& ret = DP[s][e];

    if(ret != -1) return ret;
    if (s == e) return ret = 0;
    if (s + 1 == e) return ret = File[s] + File[e];

    for (int i = s; i < e; i++) {
        int left = answer(s, i);
        int right = answer(i + 1, e);
        ret = (ret == -1) ? left + right : min(ret, left + right);
    }

    return ret += Sum[e] - Sum[s - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while(T--) {
        memset(DP, -1, sizeof(DP));
        memset(Sum, 0, sizeof(Sum));
        cin >> K;
        for (int i = 1; i <= K; i++) {
            cin >> File[i];
            Sum[i] = Sum[i - 1] + File[i];
        }
        cout << answer() << endl;
    }
    return 0;
}
