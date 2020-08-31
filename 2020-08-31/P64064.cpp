// https://programmers.co.kr/learn/courses/30/lessons/64064

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
int N;
unordered_set<int> Bitmask; // 중복 제거를 위해 set 사용

// user_id랑 banned_id가 매칭되는지 확인
bool match(string& id, string& ast) {
    if (id.size() != ast.size()) return false;
    for (int i = 0; i < id.size(); i++) {
        if (ast[i] == '*') continue;
        if (id[i] != ast[i]) return false;
    }
    return true;
}

void dfs(vector<string>& user_id, vector<string>& banned_id, int cnt = 0, int bm = 0) {
    if (cnt == N) {
        Bitmask.insert(bm);
        return;
    }
    string currBanned = banned_id[cnt];
    for (int i = 0; i < user_id.size(); i++) {
        if (!(bm & (1 << i)) && match(user_id[i], currBanned))
            dfs(user_id, banned_id, cnt + 1, bm | (1 << i));
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    N = banned_id.size();
    Bitmask.clear();
    
    dfs(user_id, banned_id);
    return Bitmask.size();
}
