// https://www.acmicpc.net/problem/1328

#include <iostream>
using namespace std;

#define MOD 1000000007

int N, L, R;
int DP[101][101][101];
// DP[i][j][k] : i개의 건물이 있을 때, 왼쪽에서 본 건물이 j개, 오른쪽에서 본 건물이 k개인 경우

int main() {
	cin >> N >> L >> R;

	DP[1][1][1] = 1;
	DP[2][2][1] = DP[2][1][2] = 1;

	// n-1 건물의 수의 상태에서 길이 1의 건물을 추가한다고 생각
	// 맨 앞에 추가하면 l이 l + 1이 되고, 맨 뒤에 추가하면 r이 r + 1이 된다. 아무데나 추가하면 변화가 없다.
	// 따라서 점화식은 DP[n][l][r] = DP[n - 1][l][r] * (n - 2) + DP[n - 1][l - 1][r] + DP[n - 1][l][r - 1]이다.
	long long int temp;
	for (int i = 3; i <= N; i++) {
		DP[i][i][1] = DP[i][1][i] = 1;
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				temp = DP[i - 1][j][k];
				temp = (temp * (i - 2)) % MOD;
				temp += (DP[i - 1][j - 1][k] % MOD);
				temp += (DP[i - 1][j][k - 1] % MOD);

				DP[i][j][k] = temp;
			}
		}
	}

	cout << DP[N][L][R] << endl;
	return 0;
} 
