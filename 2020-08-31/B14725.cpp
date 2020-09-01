// https://www.acmicpc.net/problem/14725

// 트라이로 풀었다. 트라이는 문자 하나하나를 노드에 넣는다면 문자열을 째로 노드에 넣는다.
// 다음 자식이 몇 개인지 알 수 없고, 사전순으로 정렬이 되어야 하기 때문에 자식 노드를 map으로 선언해주었다.
// 계속 결과가 이상하게 나와서 다시 보니까 26번째 줄에서 그냥 insert를 호출해서 그런거였다...

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct Node {
	map<string, Node> next;
	int depth;

	Node() {};
	Node(int depth) {
		this->depth = depth;
	}

	void insert(vector<string>& str, int cnt = 0) {
		if (str.size() <= cnt) return;
		string curr = str[cnt];
		if (!next.count(curr)) next[curr] = Node(cnt);
		next[curr].insert(str, cnt + 1);
	}

	void print() {
		for (auto node : next) {
			for (int i = 0; i < node.second.depth; i++) cout << "--";
			cout << node.first << endl;
			node.second.print();
		}
	}
} Root;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, K;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> K;
		vector<string> v;
		for (int j = 0; j < K; j++) {
			string t;
			cin >> t;
			v.push_back(t);
		}
		Root.insert(v);
	}
	Root.print();
	return 0;
}
