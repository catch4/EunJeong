// https://programmers.co.kr/learn/courses/30/lessons/67256

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int Key[][2] = { {4, 2},  // 0
               {1, 1}, {1, 2}, {1, 3},  // 1 2 3 
                {2, 1}, {2, 2}, {2, 3}, // 4 5 6
                {3, 1}, {3, 2}, {3, 3}, // 7 8 9
                {4, 1}, {4, 3}};  // * #

int calcDist(int u, int v) {
    return abs(Key[u][0] - Key[v][0]) + abs(Key[u][1] - Key[v][1]);
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int currL = 10, currR = 11;
    for (auto num : numbers) {
        char finger = ' ';
        if (num == 1 || num == 4 || num == 7) finger = 'L';
        else if (num == 3 || num == 6 || num == 9) finger = 'R';
        else {
            int distL = calcDist(currL, num);
            int distR = calcDist(currR, num);

            if (distL < distR) finger = 'L';
            else if (distL > distR) finger = 'R';
            else {
                if (hand == "left") finger = 'L';
                else if (hand == "right") finger = 'R';
            }
        }
        if (finger == 'L') currL = num;
        else if (finger == 'R') currR = num;
        answer += finger;
    }
    return answer;
}
