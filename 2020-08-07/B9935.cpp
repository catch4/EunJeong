// https://www.acmicpc.net/problem/9935

#include <iostream>
#include <string>
#define endl '/n'
using namespace std;

const int MAX = 1000001;

string Str, Bomb;
char Result[MAX];

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> Str >> Bomb;

	int idx = 0;
	for (int i = 0; i < Str.length(); i++) {
		Result[idx++] = Str[i];
		if (Result[idx - 1] == Bomb[Bomb.length() - 1]) {
			if (idx - Bomb.length() < 0)
				continue;

			bool isBomb = true;
			for (int j = 0; j < Bomb.length(); j++) {
				if (Result[idx - j - 1] != Bomb[Bomb.length() - j - 1]) {
					isBomb = false;
					break;
				}
			}

			if (isBomb)
				idx -= Bomb.length();
		}
	}

	if (!idx)
		cout << "FRULA" << endl;
	else {
		for (int i = 0; i < idx; i++)
			cout << Result[i];
		cout << endl;
	}
	return 0;
}
