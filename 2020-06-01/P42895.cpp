#include <vector>
#include <algorithm>
#define MAX 9
using namespace std;
 
int Answer;
int N, Number;
 
void dfs(int count = 0, int curr = 0) {
    if (MAX <= count) return;
    if (curr == Number) {
        Answer = min(Answer, count);
        return;
    }
    int temp = 0;
    for (int i = 0; i + count < MAX; i++) {
        // N부터 NN, NNN, NNNN ...
        temp = temp * 10 + N;
        // 더하기 빼기 곱하기 나누기
        dfs(count + 1 + i, curr + temp);
        dfs(count + 1 + i, curr - temp);
        dfs(count + 1 + i, curr * temp);
        dfs(count + 1 + i, curr / temp);
    }
}
 
int solution(int n, int number) {
    Answer = MAX;
    N = n, Number = number;
    dfs();
    // number와 맞는 경우 X : -1 리턴
    if (Answer == MAX) return -1;
    return Answer;
} 
