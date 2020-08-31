// https://www.acmicpc.net/problem/4358

// Map을 이용해 key-string, value-int Hash로 풀었다.
// 트라이로도 풀 수 있다는데.. 일단 귀찮아서 패스 ^.^

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
using namespace std;

map<string, int> Trees;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	string name;
	int total = 0;
	while (getline(cin, name)) {
		total++;
		if (!Trees[name]) Trees[name] = 0;
		Trees[name]++;
	}
	for (map<string, int>::iterator it = Trees.begin(); it != Trees.end(); it++) {
		cout << fixed << setprecision(4) << it->first << " " << (it->second / (double)total) * 100 << endl;
	}
	return 0;
}
