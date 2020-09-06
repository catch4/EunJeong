// https://www.acmicpc.net/problem/5015

// DP 테이블을 만들어서 검색하려는 문자열과 파일명을 인덱스로 한 문자씩 비교
// [1] 해당 인덱스에서 두 문자가 일치하면 다음으로 넘어감
// [2] 둘 다 문자열의 끝에 다다랐으면 가능한 경우
// [3] 검색하려는 문자열이 '*'인 경우 매치하거나 안 하거나 두 가지 경우로 나뉨

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int N, DP[101][101];  // DP[i][j]: 검색 문자열[i]와 파일명[j]를 비교한 결과
string Reg, File;

int match(int r = 0, int f = 0) {
	int& ret = DP[r][f];
	if (ret != -1) return ret;
  // [1]
	if (r < Reg.size() && f < File.size() && Reg[r] == File[f])
		return ret = match(r + 1, f + 1);
  // [2]
	if (r == Reg.size() && f == File.size())
		return ret = 1;
  // [3]
	if (Reg[r] == '*')
		if (match(r + 1, f) || (r < Reg.size() && match(r, f + 1)))
			return ret = 1;
	return ret = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> Reg >> N;
	for (int i = 0; i < N; i++) {
		cin >> File;
		memset(DP, -1, sizeof(DP));
		if (match())
			cout << File << endl;
	}
	return 0;
}
