#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main() {
    cin >> a >> b >> c;
    if(a == 1 && b == 0 && c == 0) {
        cout << "YES\n0\n";
    } else if(a > b + c) {
        cout << "YES\n" << 2 * (b + c) + 1 << '\n';
    } else {
        cout << "NO\n";
    }
}