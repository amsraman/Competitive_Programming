#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int b[4], p[4], ans = INF;
string opts[11] = {"nononon", "pnonqonon", "nopnonqon", "nonopnonq", "pnononqon", "nopnononq", "ppnonqonqon", "pnopnonqqon", "noppnonqonq", "nopnopnonqq", "pnonqopnonq"};
bool bad;

int prec(char op) {
    if(op == '*' || op == '/') {
        return 2;
    }
    if(op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

int app(int a, int b, char op) {
    if(op == '+') {
        return a + b;
    } else if(op == '-') {
        return a - b;
    } else if(op == '*') {
        return a * b;
    } else if(b == 0) {
        bad = true;
        return -1;
    } else if(a % b != 0) {
        bad = true;
    }
    return a / b;
}

int eval(string exp) {
    stack<int> vals;
    stack<char> ops;
    int cval = 0;
    bool on = false;
    for(char c: exp) {
        if(isdigit(c)) {
            cval = 10 * cval + c - '0';
            on = true;
        } else {
            if(on) {
                vals.push(cval);
                on = cval = 0;
            }
            if(c == '(') {
                ops.push(c);
            } else if(c == ')') {
                while(!ops.empty() && ops.top() != '(') {
                    int val2 = vals.top(); vals.pop();
                    int val1 = vals.top(); vals.pop();
                    char op = ops.top(); ops.pop();
                    vals.push(app(val1, val2, op));
                }
                ops.pop();
            } else {
                while(!ops.empty() && prec(ops.top()) >= prec(c)) {
                    int val2 = vals.top(); vals.pop();
                    int val1 = vals.top(); vals.pop();
                    char op = ops.top(); ops.pop();
                    vals.push(app(val1, val2, op));
                }
                ops.push(c);
            }
        }
    }
    if(on) {
        vals.push(cval);
    }
    while(!ops.empty()) {
        int val2 = vals.top(); vals.pop();
        int val1 = vals.top(); vals.pop();
        char op = ops.top(); ops.pop();
        vals.push(app(val1, val2, op));
    }
    return vals.top();
}

int inv() {
    int tmp[4], ret = 0;
    for(int i = 0; i < 4; i++) {
        tmp[i] = p[i];
    }
    for(int i = 0; i < 4; i++) {
        int j = i;
        while(tmp[j] != b[i]) {
            ++j;
        }
        ret += (j - i);
        while(j > i) {
            swap(tmp[j], tmp[j - 1]);
            --j;
        }
    }
    return ret;
}

int score(string exp) {
    int parens = 0;
    for(char c: exp) {
        parens += (c == '(');
    }
    return 2 * inv() + parens;
}

int main() {
    for(int i = 0; i < 4; i++) {
        cin >> b[i];
        p[i] = b[i];
    }
    sort(p, p + 4);
    do {
        for(int op = 0; op < 64; op++) {
            string ops[3];
            int tmp = op;
            for(int i = 0; i < 3; i++) {
                int rem = tmp & 3;
                if(rem == 0) {
                    ops[i] = "+";
                } else if(rem == 1) {
                    ops[i] = "-";
                } else if(rem == 2) {
                    ops[i] = "*";
                } else {
                    ops[i] = "/";
                }
                tmp >>= 2;
            }
            for(string o: opts) {
                string exp;
                for(int i = 0, j = 0, k = 0; i < o.length(); i++) {
                    if(o[i] == 'p') {
                        exp += "(";
                    } else if(o[i] == 'q') {
                        exp += ")";
                    } else if(o[i] == 'n') {
                        exp += to_string(p[j]);
                        ++j;
                    } else {
                        exp += ops[k];
                        ++k;
                    }
                }
                bad = false;
                if((eval(exp) == 24) && (!bad)) {
                    ans = min(ans, score(exp));
                }
            }
        }
    } while(next_permutation(p, p + 4));
    if(ans == INF) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }
}