template <typename T>
T ShuntingYard(string exp) {
    auto prec = [](char op) {
        if(op == '*' || op == '/') {
            return 2;
        } else if(op == '+' || op == '-') {
            return 1;
        }
        return 0;
    };

    auto app = [](T a, T b, char op) {
        if(op == '+') {
            return a + b;
        } else if(op == '-') {
            return a - b;
        } else if(op == '*') {
            return a * b;
        }
        return a / b;
    }

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
    return vals.top();
}