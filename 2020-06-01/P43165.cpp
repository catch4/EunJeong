// 프로그래머스 - 타겟넘버
// https://programmers.co.kr/learn/courses/30/lessons/43165

#include <string>
#include <vector>
#include <cstring>

using namespace std;
vector<int> Nums;
int Answer, N, T;

void dfs(int i = 0, int sum = 0) {
    if (i == N) {
        if (sum == T) {
            Answer++;
        }
        return;
    }
    dfs(i + 1, sum + Nums[i]);  // 해당 인덱스의 값을 더하는 경우
    dfs(i + 1, sum - Nums[i]);  // 해당 인덱스의 값을 빼는 경우
}

int solution(vector<int> numbers, int target) {
    // init
    Nums = numbers;
    Answer = 0, N = numbers.size(), T = target;
    memset(Check, false, sizeof(Check));
    
    // DFS 진행
    dfs();
    return Answer;
} 
