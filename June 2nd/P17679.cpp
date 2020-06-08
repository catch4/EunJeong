// https://programmers.co.kr/learn/courses/30/lessons/17679

#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int sq[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
int M, N;
char Board[31][31];
bool Pop[31][31];

int play() {
    int ret = 0;
    // 2x2로 터질 수 있는지 확인
    for (int i = 0; i < M - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (!Board[i][j]) continue;
            bool square = true;
            for (int k = 1; k < 4; k++) {
                if (Board[i][j] != Board[i + sq[k][0]][j + sq[k][1]]) {
                    square = false;
                    break;
                }
            }
            // 터질 수 있다면 true
            if (square) {
                for (int k = 0; k < 4; k++) {
                    Pop[i + sq[k][0]][j + sq[k][1]] = true;
                }
            }
        }
    }
    
    // 블록 내리기
    char tmpBoard[31][31];
    for (int j = 0; j < N; j++) {
        int id = M - 1;
        for (int i = M - 1; 0 <= i; i--) {
            if (Pop[i][j]) ret++;
            else {
                tmpBoard[id][j] = Board[i][j];
                id--;
            }
        }
        for (int i = id; 0 <= i; i--) {
            tmpBoard[i][j] = 0;
        }
    }
    memcpy(Board, tmpBoard, sizeof(tmpBoard));
    
    // 다음 탐색을 위해 Pop 초기화
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            Pop[i][j] = false;
        }
    }
    return ret;
}

int solution(int m, int n, vector<string> board) {
    M = m, N = n;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            Board[i][j] = board[i][j];
        }
    }
    
    int answer = 0;
    while (int blocks = play()) {
        answer += blocks;
    }
    return answer;
}
