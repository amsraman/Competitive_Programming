#include <bits/stdc++.h>

using namespace std;

template <typename T>
T shunting_yard(string exp) {
    bool bad = false;

    auto prec = [](char op) {
        return 0;
    };

    auto app = [&](T a, T b, char op) {
        if(op == '+') {
            return a + b;
        } else if(op == '-') {
            return a - b;
        } else if(op == '*') {
            return a * b;
        }
        if(a % b != 0 || b == 0) b = 1, bad = true;
        return a / b;
    };

    stack<T> vals;
    stack<char> ops;
    T cval = 0;
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
                    T val2 = vals.top(); vals.pop();
                    T val1 = vals.top(); vals.pop();
                    char op = ops.top(); ops.pop();
                    vals.push(app(val1, val2, op));
                }
                ops.pop();
            } else {
                while(!ops.empty() && prec(ops.top()) >= prec(c)) {
                    T val2 = vals.top(); vals.pop();
                    T val1 = vals.top(); vals.pop();
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
        T val2 = vals.top(); vals.pop();
        T val1 = vals.top(); vals.pop();
        char op = ops.top(); ops.pop();
        vals.push(app(val1, val2, op));
    }
    return (bad ? -1 : vals.top());
}

int main() {
    int a, b, c, ans = 1e9; cin >> a >> b >> c;
    string ops = "+-*/", sa = to_string(a), sb = to_string(b), sc = to_string(c);
    for(char c1: ops) {
        for(char c2: ops) {
            string exp = sa + c1 + sb + c2 + sc;
            int res = shunting_yard<int>(exp);
            if(res >= 0) ans = min(ans, res);
        }
    }
    cout << ans << '\n';
}