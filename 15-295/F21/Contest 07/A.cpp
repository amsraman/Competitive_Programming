#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {
    cin >> a >> b;
    if(a - abs(a - b) - 1 >= 0) {
        cout << 0 << endl;
    } else {
        cout << a + abs(a - b) + 1 << endl;
    }
}