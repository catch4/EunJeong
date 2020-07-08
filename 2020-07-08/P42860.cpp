// https://programmers.co.kr/learn/courses/30/lessons/42860
// 처음에는 오른쪽으로 갔다가 왼쪽으로 가거나, 왼쪽으로 갔다가 오른쪽으로 방향을 바꾸는 경우를 생각하지 않고
// 단순하게 A가 연속인 부분을 찾아서 최소가 되는 한 방향으로만 이동하게 구현했는데 테스트 11에서 실패했다.
// 반례를 찾아보니 "BBBBAAAAB"처럼 방향을 바꿨을 때 최소가 되는 경우가 생겨서 어떡해야하나 고민하다가 그냥 문자열을 돌렸다. (왔다갔다 거리는 경우는 없을테니까)
// "BBBBAAAAB" -> "BBBAAAABB" -> "BBAAAABBB" -> ... 의 경우를 모두 탐색해도 문자열의 길이가 최대 20이라 괜찮았다.

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(string name) {
    int ret = 0x7FFFFFFF; 
    // j - 시작하는 문자열의 위치
    for (int j = 0; j < name.size(); j++) {
        string str = "";
        int answer = j; // 문자열을 돌렸기 때문에 횟수를 더한 채로 시작
        // 돌린 문자열 만들어주기
        for (int k = j; str.size() != name.size(); k = (k + 1) % name.size()) {
            str += name[k];
        }
        // 'A'와 문자의 차이를 더해준다 (해당 위치에서 어차피 바꿔야 하므로)
        for (int i = 0; str[i]; i++) {
            int min_val = min(str[i] - 'A', 26 - (str[i] - 'A'));
            answer += min_val;
        }
        // 앞으로 갈지 뒤로 갈지를 결정하는건 1번 인덱스부터 있는 연속된 A의 개수와
        // 제일 끝에 연속된 A의 개수라고 생각해서 앞 뒤에 있는 A의 개수를 세었다.
        int front = 0, end = 0;
        for (int i = 1; str[i]; i++) {
            if (str[i] != 'A') break;
            front++;
        }
        for (int i = str.size() - 1; 0 <= i; i--) {
            if (str[i] != 'A') break;
            end++;
        }
        answer += (str.size() - max(front, end) - 1);
        if (answer < ret) ret = answer;
    }
    // 'A'로만 이루어진 경우 38번째 줄에서 -1이 나오기 때문에 추가
    if (ret == -1) ret = 0;
    return ret;
}
