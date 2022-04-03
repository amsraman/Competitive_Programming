#include <bits/stdc++.h>

using namespace std;

int t;
string n;

string ins(char c) {
    string tmp = c + n;
    int len = tmp.length();
    for(int i = 0; (i < len - 1 && (tmp[0] == '0' || tmp[i] >= tmp[i + 1])); i++) {
        swap(tmp[i], tmp[i + 1]);
    }
    return tmp;
}

int main() {
    cin >> t;
    for(int _  = 1; _ <= t; _++) {
        cin >> n;
        int sum = 0;
        for(char c: n) {
            sum += (c - '0');
            sum %= 9;
        }
        cout << "Case #" << _ << ": ";
        if(sum == 0) {
            string s1 = ins('0'), s2 = ins('9');
            if(s1 < s2) {
                cout << s1 << endl;
            } else {
                cout << s2 << endl;
            }
        } else {
            cout << ins(char('0' + 9 - sum)) << endl;
        }
    }
}