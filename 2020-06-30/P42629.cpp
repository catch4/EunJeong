// https://programmers.co.kr/learn/courses/30/lessons/42629

// # testcase 1: 3, [1], [1], 2 - Answer 0
// # testcase 2: 4, [1, 2, 3, 4], [10, 40, 20, 30], [100] - Answer 4

// 테스트 11만 틀리길래 질문하기를 확인하고 2번 testcase를 추가해 확인했다.
// 알고 보니 vector를 끝까지 다 도는 경우를 확인하지 않아서
// idx의 값이 바뀌지 않았고, 결국 중복 push가 발생했던 거였다.

#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    if (k <= stock) return 0; // 1번 testcase 때문에 추가
    
    int answer = 0;
    priority_queue<pair<int, int>> pq;
    int curr_day = stock, idx = 0;
    while (true) {
        for (int i = idx; i <= dates.size(); i++) {
            if (curr_day < dates[i] || i == dates.size()) { // 2번 testcase 때문에 추가
                idx = i;
                break;
            }
            pq.push({ supplies[i], dates[i] });
        }
        curr_day += pq.top().first;
        pq.pop(); answer++;
        if (k <= curr_day) break;
    }
    return answer;
} 
