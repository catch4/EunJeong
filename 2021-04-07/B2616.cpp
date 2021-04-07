// https://www.acmicpc.net/problem/2616

#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int N, M, Answer;
int Carriages[50001];
int S[50001];   // 부분합을 바로 계산하기 위해 누적합 미리 구해두기
int DP[4][50001];
// DP[i][j]: 소형기관차를 i대 운행할 때 j번째 객차를 선택했을 경우 최댓값

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> Carriages[i];
        S[i] = S[i - 1] + Carriages[i];
    }
    cin >> M;
    
    for (int i = 1; i <= 3; i++) {
        for (int j = i * M; j <= N; j++) {
            int partial_sum = S[j] - S[j - M];
            if (i == 1)
                DP[i][j] = max(DP[i][j - 1], partial_sum);
            else 
                DP[i][j] = max(DP[i][j - 1], DP[i - 1][j - M] + partial_sum);
            Answer = max(Answer, DP[i][j]);
        }
    }
    cout << Answer << endl;
    return 0;
}
