// https://www.acmicpc.net/problem/6209

// 예전에 백준에서 풀어봤던 공유기 문제가 생각나서 비슷한 방식으로 접근했다.
// mid를 뛰는 거리, cnt를 밟은 돌섬의 개수로 두고,
// cnt가 N - M보다 작으면 더 밟아야 한다는 거니까 거리를 줄이고
// N - M보다 크면 덜 밟아야 한다는 거니까 거리를 늘려줬다.
// 계속 틀리길래 평소의 이분탐색처럼 등호 문제인가 싶어서 이런 저런 조합을 다 시도했는데,
// 결론적으로는 그것과 별개로 ans 변수를 따로 두지 않고 정답으로 mid를 출력한 것이 문제였다.
// left를 mid + 1로 갱신해줄 때 ans를 mid로 갱신하는 부분만 추가하니 해결되었다.
// 이분탐색 너무 싫다 ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ

#include <iostream>
#include <algorithm>
using namespace std;

int D, N, M;
int Island[50001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> D >> N >> M;
	for (int i = 0; i < N; i++) cin >> Island[i];
	sort(Island, Island + N);

	int left = 0, right = D, ans = 0;
	while (left <= right) {
		int mid = (left + right) / 2;
		int cnt = 0, curr = 0, id = 0;
		while (curr < D) {
			curr += mid;
			for (int i = id; i < N; i++) {
				if (curr <= Island[i]) {
					cnt++;
					curr = Island[i];
					id = i + 1;
					break;
				}
			}
		}
		if (cnt < N - M) right = mid - 1;
		else left = mid + 1, ans = mid;
	}
	cout << ans << endl;
	return 0;
}
