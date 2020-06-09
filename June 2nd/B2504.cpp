// https://www.acmicpc.net/problem/2504
// 괄호, 짝짓기만 보면 무조건 스택이 떠오름.. ㅎㅎ;

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// < 생각한 방법 >
// 1. 여는 괄호인 경우: stack에 push한다.
// 2. 닫는 괄호인 경우:
//	 1) stack의 top에 짝이 맞는 괄호가 바로 있을 경우 pop하고 2 또는 3을 push한다.
//	 2) 이전에 계산한 숫자가 있을 경우 짝이 맞는 괄호가 나올 때까지 더하고 계산값을 push한다.
// 3. 예외처리  <- 여기서 애를 엄청 많이 먹었다!!! ㅠ_ㅠ
//	 1) stack의 top을 확인하거나 pop을 할 때 stack이 empty인지 무조건 확인해야 한다.
//	 2) 2-2에서 여는 짝 괄호가 나오기 전에 다른 괄호가 나오면 올바르지 않은 문자열이다.

// 처음에 stack이 비어있는 경우를 확인 안 하는 바람에 런타임 에러를 잔뜩 얻었다 ㅎㅎ;
// 여러 수정을 거쳐 위 방법까지 구현했는데도 "틀렸습니다"가 나와서 생각해보니...
// 3-2의 예외처리를 할 때 짝 괄호가 아닌 경우를 결정짓는 과정에서
// 2와 3을 곱하거나 더한 숫자로 괄호의 ascii 값이 나올 수 있을 것 같았다. (즉, 괄호의 아스키값과 stack의 계산값이 같은 경우)
// 그래서 괄호를 넣을 때 괄호 그 자체로 넣어주는 것이 아니라 절대 나올 일 없는 음수 값으로 stack에 넣어주었다.
// (, [, ), ] 순서대로 -1, -2, -3, -4 값을 대응했다. 그랬더니 맞았습니다!!가 나왔다 ㅠ_ㅠ

// stack 문제라는 것은 바로 생각했는데 예외처리가 특히 어려웠던 것 같다. 
// 그래서 이리저리 찾아봤는데 사람마다 푼 게 은근 달라서 모르겠음.. 스터디에서 얘기할 거리가 있을 듯 하다!

int main() {
	string input;
	cin >> input;

	stack<int> s;
	int check = 0;
	bool able = true;
	for (int i = 0; i < input.length(); i++) {
		char c = input[i];
		if (c == '(' || c == '[') {
			check++;
			s.push((c == '(')? -1 : -2);
			continue;
		}

		check--;
		if (s.empty() || check == -1) {
			able = false;
			break;
		}

		if (c == ')') {
			if (s.top() == -1) {
				s.pop();
				s.push(2);
			}
			else {
				int tmp = 0;
				while (!s.empty() && s.top() != -1) {
					if (s.top() == -2 || s.top() == -3 || s.top() == -4) {
						able = false;
						i = input.length();
						break;
					}
					tmp += s.top();
					s.pop();
				}
				if (s.empty()) {
					able = false;
					break;
				}
				s.pop();
				s.push(tmp * 2);
			}
		}
		else if (c == ']') {
			if (s.top() == -2) {
				s.pop();
				s.push(3);
			}
			else {
				int tmp = 0;
				while (!s.empty() && s.top() != -2) {
					if (s.top() == -1 || s.top() == -3 || s.top() == -4) {
						able = false;
						i = input.length();
						break;
					}
					tmp += s.top();
					s.pop();
				}
				if (s.empty()) {
					able = false;
					break;
				}
				s.pop();
				s.push(tmp * 3);
			}
		}
	}

	if (check || !able) {
		cout << 0 << endl;
		return 0;
	}

	int answer = 0;
	while (!s.empty()) {
		answer += s.top();
		s.pop();
	}
	cout << answer << endl;
	return 0;
}
