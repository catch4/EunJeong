// https://programmers.co.kr/learn/courses/30/lessons/43238

// 이분탐색 lower-bound. 21번째 줄이 핵심인듯.
// 8번 케이스만 틀리길래 질문하기를 참고했다. right를 long long으로 형변환 해주니 통과됐다.
// 아마 8번 케이스의 마지막 원소가 매우 커서 오버플로우가 나는 듯.

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    
    long long left = 0;
    long long right = (long long)(times[times.size() - 1]) * n;
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long  people = 0;
        for (auto t : times)
            people += (mid / t);
        if (n <= people)
            right = mid - 1;
        else left = mid + 1;
    }
    return left;
}
