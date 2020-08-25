// https://www.acmicpc.net/problem/15998

// 딱 보고 최소공배수를 쓰는 건 바로 간파했고, gcd 함수도 외우고 있었어서 쉽게 풀릴 줄 알았는데...
// 엄청 오래 걸렸다 ㅠ ㅋㅋㅋㅋ 진짜 역대급으로 뻘짓을 많이 한 문제같다. 카카오는 나랑 안 맞다 ㅡㅡ

// [1] 로그 유효성 판별
// 주어진 로그도 유효성 여부를 판단해야하는지 몰라서 무조건 옳은 경우만 있다고 가정하고 풀었는데
// 틀릴리가 없는데도 계속 틀려서 검색해보고서야 로그 유효성 여부도 판단해야하는지 깨달았다.. ^^

// [2] minB를 갱신하는 시점
// a, b 입력과 동시에 minB를 바로 갱신해줘서 63%?정도까지 올라가고 계속 틀렸다.
// minB 때문에 틀렸다는걸 생각지도 못하고 다른 조건을 계속 바꿔서 덕분에 틀렸습니다 와장창... ㅋㅋㅋㅋ
// 돈을 사용하는, 즉, (a < 0)인 경우만 minB를 갱신했더니 바로 맞았습니다가 나와서 완전 허무했다 ㅠ

// 그 외에는 각 경우마다 나눠서 M만 갱신하면 됐기 때문에 어려울게 전혀 없었는데 ㅠㅠㅠ
// 따흑 수학으로 분류되는 문제는 아직도 너무 어렵다 ㅠㅠㅠㅠㅠ

#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

const ll MAX = pow(10, 18);
ll N, M = -1;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll answer() {
	ll a, b, prev = 0, minB = MAX;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		// <입금>
		if (a > 0) {
			// 금액이 안 맞으면 안됨
			if (prev + a != b) return -1;
		}
		// <사용>
		else if (a < 0) {
			ll recharge = b - prev - a;	// 충전 액수

			// 충전할 필요가 없는 경우
			if (0 <= prev + a) {
				// 충전하면 안됨
				if (recharge) return -1;
			}

			// 충전해야 하는 경우
			else {
				// 충전을 안하면 안됨
				if (recharge <= 0) return -1;

				// 값 갱신
				M = gcd(recharge, M);
				if (b && b < minB) minB = b;

				// 필요 이상으로 충전하면 안됨
				if (minB != MAX && M <= minB) return -1;
				// 최소 충전 금액이 1인데 잔액이 있으면 안됨
				if (M == 1 && b) return -1;
			}
		}
		prev = b;
	}
	// M == 0이면 충전을 하지 않았으므로 1 리턴
	return M ? M : 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	cout << answer() << endl;
	return 0;
}
