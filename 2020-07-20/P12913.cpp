// https://programmers.co.kr/learn/courses/30/lessons/12913

// 행의 개수가 100,000이므로 DFS 쓰면 시간초과
// 각 행에 대하여 이전 행에서 같은 열은 제외하고 max값을 찾고
// 그 값에 land 값을 더해준 것과 현재 DP 값 중 최댓값으로 갱신

#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int DP[100001][4];

int solution(vector<vector<int>> land) {
    int answer = 0;
    
    /* init */
    N = land.size();
    memset(DP, 0, sizeof(DP));
    for (int i = 0; i < 4; i++) DP[0][i] = land[0][i];
    
    /* DP */
    for(int r = 1; r < N; r++) {
        for (int c = 0; c < 4; c++) {
            int curr = land[r][c];
            for (int d = 0; d < 4; d++) {
                if(c == d) continue;
                int prev = DP[r - 1][d];
                DP[r][c] = max(prev + curr, DP[r][c]);
            }
        }
    }
    
    /* Find max value in the last raw of DP table */
    for (int i = 0; i < 4; i++) {
        if (answer < DP[N - 1][i]) answer = DP[N - 1][i];
    }
    return answer;
}
