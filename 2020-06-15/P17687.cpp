// https://programmers.co.kr/learn/courses/30/lessons/17687

#include <string>
#include <vector>

using namespace std;
const string HEX[16] = "0123456789ABCDEF";

// 숫자 x을 n진수로
string convert(int x, int n) {
    if (x == 0) return "0";
    string ret = "";
    while (x) {
        ret = HEX[x % n] + ret;
        x /= n;
    }
    return ret;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    int turn = 0, num = 0;
    while(true) {
        string tmp = convert(num, n);
        for (int i = 0; i < tmp.length(); i++) {
            turn++;
            if (turn % m == (p % m)) answer += tmp[i];
            if (answer.size() == t) return answer;
        }
        num++;
    }
    return answer;
}
