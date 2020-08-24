// https://programmers.co.kr/learn/courses/30/lessons/60058

#include <string>
#include <vector>
#include <stack>

using namespace std;

// 올바른 괄호 문자열인지 판단하는 함수
bool is_right(string& str) {
    if (!str.size()) return true;
    stack<char> s;
    if (str[0] == ')') return false;
    else s.push(str[0]);
    
    for (int i = 1; str[i]; i++) {
        if (str[i] == ')') {
            if (s.empty()) return false;
            s.pop();
        }
        else if (str[i] == '(')
            s.push('(');
    }
    if (s.empty()) return true;
    else return false;
}

// u가 올바른 문자열이 아닌 경우 앞뒤를 자르고 괄호를 바꾸는 함수
string makeStr(string u) {
    if (u.size() <= 2) return "";
    string ret = "";
    for (int i = 1; i < u.size() - 1; i++) {
        ret += (u[i] == '(' ? ')' : '(');
    }
    return ret;
}

// 문자열에 대해 반복적으로 해당 과정을 수행하는 함수
string recur(string p) {
    if (p.size()) {
        int cnt = (p[0] == '(' ? 1 : -1);
        int off = 1;
        while(cnt) {
            cnt += (p[off++] == '(' ? 1 : -1);
        }
        string u = p.substr(0, off);  // 문자 처음부터 off - 1까지
        string v = p.substr(off);     // off부터 문자 끝까지
        
        // u가 올바른 문자열인 경우
        if (is_right(u))
            return u + recur(v);
        // u가 올바른 문자열이 아닌 경우
        else
            return '(' + recur(v) + ')' + makeStr(u);
    }
    return "";
}

string solution(string p) {
    return recur(p);
}
