#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    sort(jobs.begin(), jobs.end());
    priority_queue<pair<int, int>> pq;
    
    int time = 0, idx = 0, cnt = 0;
    while (true) {
        if (cnt == jobs.size()) break;
        for (int i = idx; i <= jobs.size(); i++) {
            if (time < jobs[i][0] || i == jobs.size()) {
                idx = i;
                break;
            }
            pq.push({ jobs[i][0], -jobs[i][1] });
        }
        if (!pq.empty()) {
            int request = pq.top().first;
            int duration = -pq.top().second;
            pq.pop();
            
            time += duration;
            answer += (time - request);
            cnt++;
        }
        else
            time++;
    }
    return answer / jobs.size();
}
