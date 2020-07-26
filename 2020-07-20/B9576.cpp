// https://www.acmicpc.net/problem/9576

// 처음에 대강 a, b로 정렬해서 풀면 되겠다 싶어서
// a로 정렬했고 이수 님이 올려주신 테스트 케이스도 다 맞는데
// 50% 이상 퍼센트가 올라가다가 틀렸습니다가 나왔다. ㅠ
// b로 정렬하니 바로 맞출 수 있는 문제였고,
// 생각해보니 예전 프로그래머스에서도 비슷한 문제를 푼 적이 있는 것 같다..^^..

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M;
vector<pair<int, int>> Books;
bool Occupied[1001];

bool cmp(const pair<int, int>& u, const pair<int, int>& v) {
	if (u.second < v.second) return true;
	else if (u.second == v.second)
		if (u.first < v.first) return true;
	return false;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N >> M;
		Books.clear();
		memset(Occupied, false, sizeof(Occupied));

		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			Books.push_back({ a, b });
		}
		sort(Books.begin(), Books.end(), cmp);

		int ans = 0;
		for (int i = 0; i < Books.size(); i++) {
			int a = Books[i].first, b = Books[i].second;
			for (int j = a; j <= b; j++) {
				if (!Occupied[j]) {
					Occupied[j] = true;
					ans++;
					break;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}

// a로 정렬해서 틀린 코드
/*
int ans = 0;
for (int i = 0; i < M; i++) {
	int a, b;
	cin >> a >> b;
	// 범위가 책 한 권이면 바로 할당
	if (a == b) {
		if (Occupied[a]) continue;
		ans++;
		Occupied[a] = true;
	}
	else Books.push_back({ a, b });
}
sort(Books.begin(), Books.end());

int currBook = 1;
for (int i = 0; i < Books.size(); i++) {
	// 할당하지 않은 책이 나올 때까지 책 번호 증가
	while (Occupied[currBook]) { currBook++; }
	int a = Books[i].first, b = Books[i].second;

	// 현재 책 번호가 범위 내에 있으면 해당 책 할당
	if (a <= currBook && currBook <= b) {
		currBook++;
		ans++;
	}
	// a보다 작은 경우 바로 a 책 할당
	else if (currBook < a) {
		currBook = a;
		currBook++;
		ans++;
	}
}
*/
