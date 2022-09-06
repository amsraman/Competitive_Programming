#include <bits/stdc++.h>

using namespace std;

int main() {
    while(true) {
        int a, b, c, k;
        cin >> a >> b >> c >> k;
        if(a + b + c + k == 0) {
            break;
        }
        if(a > b) swap(a, b);
        if(a > c) swap(a, c);
        if(b > c) swap(b, c);
        int rep = 2;
        if(2 * a == b && 3 * a == c) {
            rep = 4;
        } else if(2 * a == b || 2 * a == c) {
            rep = 3;
        }
        for(int i = 0, pile; i < k; i++) {
            cin >> pile;
            cout << (pile / (a * rep)) * a + (pile % a) << " ";
        }
        cout << endl;
    }
}