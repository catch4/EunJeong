// https://www.acmicpc.net/problem/2109

#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
using namespace std;

int N, Answer;
vector< pair<int, int> > PD;
bool Checked[10001];

bool cmp(pair<int, int> u, pair<int, int> v) {
    if (u.first == v.first) return u.second > v.second;
    return u.first > v.first;
}

int main() {
    cin >> N;
    Answer = 0;
    for (int i = 0; i < N; i++) {
        int p, d;
        cin >> p >> d;
        PD.push_back(make_pair(p, d));
    }
    sort(PD.begin(), PD.end(), cmp);

    for (int i = 0; i < N; i++) {
        for (int j = PD[i].second; 1 <= j; j--) {
            if (!Checked[j]) {
                Checked[j] = true;
                Answer += PD[i].first;
                break;
            }
        }
    }

    cout << Answer << endl;
    return 0;
}
