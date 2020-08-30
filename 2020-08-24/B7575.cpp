// https://www.acmicpc.net/problem/7575

// 첫번째 프로그램 코드를 앞에서부터 K만큼 잘라 바이러스 가능성이 있는 코드로 만든다.
// (이때, K보다 큰 문자열은 생각할 필요가 없다. K보다 큰 문자열에 어찌됐든 K만큼이 포함돼 있을 것이기 때문.)
// 바이러스 가능성이 있는 코드와 그것을 뒤집은 코드를 나머지 프로그램들과 KMP 알고리즘으로 비교한다.
// 모든 다른 프로그램에 대해 바이러스 코드가 있다면 바로 YES를 출력하고 끝낸다.
// KMP 알고리즘을 공부하고 직접 구현했던게 꽤 오래돼서 방식은 생각이 나는데 정확하지 않아 다시 공부했다 ㅠ

#include <iostream>
#include <vector>
using namespace std;

int N, K;
vector<int> Program[1000];

vector<int> make_pi(vector<int>& code) {
	int size = code.size(), j = 0;
	vector<int> pi(size, 0);
	for (int i = 1; i < size; i++) {
		while (0 < j && code[i] != code[j])
			j = pi[j - 1];
		if (code[i] == code[j]) pi[i] = ++j;
	}
	return pi;
}

bool kmp(vector<int>& program, vector<int>& virus) {
	auto pi = make_pi(virus); int j = 0;
	for (int i = 0; i < program.size(); i++) {
		while (j > 0 && program[i] != virus[j])
			j = pi[j - 1];
		if (program[i] == virus[j]) {
			if (j == K - 1) return true;
			else j++;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int len; cin >> len;
		for (int j = 0; j < len; j++) {
			int num; cin >> num;
			Program[i].push_back(num);
		}
	}
	int pos = 0;
	for (int i = pos; i < Program[0].size() - K + 1; i++) {
		vector<int> virus(K);
		vector<int> reversed_virus(K);
		bool found = true;
		for (int j = 0; j < K; j++) {
			virus[j] = reversed_virus[K - j - 1] = Program[0][i + j];
		}
		for (int j = 1; j < N; j++) {
			if (kmp(Program[j], virus) || kmp(Program[j], reversed_virus)) continue;
			found = false;
			break;
		}
		if (found) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
