// https://www.acmicpc.net/problem/13325

#include <iostream>
#include <algorithm>
using namespace std;

int K, Nodes[(1 << 22)], Answer;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> K;
    for (int i = 2; i < (1 << (K + 1)); i++) {
        cin >> Nodes[i];
        Answer += Nodes[i];
    }
    for (int i = K; i > 0; i--) {
        for (int j = (1 << i); j < (1 << (i + 1)); j += 2) {
            Answer += abs(Nodes[j] - Nodes[j + 1]);
            Nodes[j / 2] += max(Nodes[j], Nodes[j + 1]);
        }
    }
    cout << Answer;
    return 0;
}
