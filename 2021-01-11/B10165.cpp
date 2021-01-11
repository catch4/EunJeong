// https://www.acmicpc.net/problem/10165
// 모르겠어서 ㅠ 검색했습니다..

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>

#define ll long long
#define pii pair<int,int>

using namespace std;

typedef struct bus {
	int num, a, b;
} Bus;

ll N, M;
bool able[500001];
vector<Bus> route1, route2;

bool compare(const Bus& f, const Bus& s) {
	if (f.a != s.a) return f.a < s.a;
	else return f.b > s.b;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	ll minA = 1e12, maxB = -1;

	for (int i = 1; i <= M; i++) {
		ll a, b; cin >> a >> b;
		Bus bus;
		bus.num = i; bus.a = a; bus.b = b;
        
		if (a - b <= 0) {
			route1.push_back(bus);
		}
		else {
			minA = min(minA, a);
			maxB = max(maxB, b);
			bus.b = b + N;
            
			route2.push_back(bus);
		}
		able[i] = true;
	}

	sort(route1.begin(), route1.end(), compare);
	sort(route2.begin(), route2.end(), compare);

	int right = 0;
	for (int i = 0; i < route1.size(); i++) {
		if (minA <= route1[i].a) able[route1[i].num] = false;
		if (maxB >= route1[i].b) able[route1[i].num] = false;

		if (route1[i].b <= right) {
			able[route1[i].num] = false;
		}
		else {
			right = route1[i].b;
		}
	}

	right = 0;
	for (int i = 0; i < route2.size(); i++) {
		// 일반적인 경우로 취급
		if (route2[i].b <= right) {
			able[route2[i].num] = false;
		}
		else {
			right = route2[i].b;
		}
	}

	for (int i = 1; i <= M; i++) {
		if (able[i] == true) {
			cout << i << ' ';
		}
	}

	return 0;
}
