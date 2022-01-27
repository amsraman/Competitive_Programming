#include <bits/stdc++.h>

using namespace std;

int c;
char board[3][3];

bool wins(char p) {
    for(int i = 0; i < 3; i++) {
        bool row = true, col = true;
        for(int j = 0; j < 3; j++) {
            row &= (board[i][j] == p);
            col &= (board[j][i] == p);
        }
        if(row || col) {
            return true;
        }
    }
    bool diag1 = true, diag2 = true;
    for(int i = 0; i < 3; i++) {
        diag1 &= (board[i][i] == p);
        diag2 &= (board[2 - i][i] == p);
    }
    return diag1 || diag2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> c;
    while(c--) {
        string state;
        cin >> state;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
        reverse(state.begin(), state.end());
        int len = state.length();
        for(int i = 0; i < min(3, len); i++) {
            int cur = state[i] - '0';
            for(int j = 0; j < 3; j++) {
                if(cur & (1 << j)) {
                    board[i][j] = 'O';
                }
            }
        }
        for(int i = 3; i < min(6, len); i++) {
            int cur = state[i] - '0';
            for(int j = 0; j < 3; j++) {
                if(cur & (1 << j)) {
                    board[i - 3][j] = 'X';
                }
            }
        }
        if(wins('O')) {
            cout << "O wins\n";
        } else if(wins('X')) {
            cout << "X wins\n";
        } else if(len >= 3 && state.substr(0, 3) == "777") {
            cout << "Cat's\n";
        } else {
            cout << "In progress\n";
        }
    }
}