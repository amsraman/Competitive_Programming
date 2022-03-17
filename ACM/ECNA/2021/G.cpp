#include <bits/stdc++.h>

using namespace std;

string op;
string num1, num2, num3;

bool is_valid(string n1, string n2, string n3) {
    int i1 = atoi(n1.c_str());
    int i2 = atoi(n2.c_str());
    int i3 = atoi(n3.c_str());
    if (op == "*") {
        return 1LL * i1 * i2 == i3;
    }
    return i1 + i2 == i3;
}

string get_substr(string s, int b, int e) {
    return s.substr(b, e - b + 1);
}

string format(string n1, string n2, string n3) {
    return n1 + " " + op + " " + n2 + " = " + n3;
}

string get_sol(string n1, string n2, string n3) {
    int len1 = n1.length(), len2 = n2.length(), len3 = n3.length();
    for(int i = 0; i < len1 - 1; i++) {
	for(int j = 0; j < len2 - 1; j++) {
            string swp1 = get_substr(n2, 0, j) + get_substr(n1, i + 1, len1 - 1);
            string swp2 = get_substr(n1, 0, i) + get_substr(n2, j + 1, len2 - 1);
            if(is_valid(swp1, swp2, n3)) {
                return format(swp1, swp2, n3);
            }
        }
    }
    for(int i = 0; i < len1 - 1; i++) {
        for(int j = 0; j < len3 - 1; j++) {
            string swp1 = get_substr(n3, 0, j) + get_substr(n1, i + 1, len1 - 1);
            string swp2 = get_substr(n1, 0, i) + get_substr(n3, j + 1, len3 - 1);
            if(is_valid(swp1, n2, swp2)) {
                return format(swp1, n2, swp2);
            }
        }
    }
    for(int i = 0; i < len2 - 1; i++) {
        for(int j = 0; j < len3 - 1; j++) {
            string swp1 = get_substr(n3, 0, j) + get_substr(n2, i + 1, len2 - 1);
            string swp2 = get_substr(n2, 0, i) + get_substr(n3, j + 1, len3 - 1);
            if(is_valid(n1, swp1, swp2)) {
                return format(n1, swp1, swp2);
            }
        }
    }
    return "";
}

int main() {
    char hi;
    cin >> num1 >> op >> num2 >> hi >> num3;
    cout << get_sol(num1, num2, num3) << endl;
}