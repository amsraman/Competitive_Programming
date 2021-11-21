#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll q;

bool isPrime(ll p) {
    for(ll i = 2; i * i <= p; i++) {
        if(p % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> q;
    if(isPrime(q)) {
        cout << 1 << endl << 0 << endl;
    } else {
        int pc = 0;
        ll mv1 = 1;
        for(ll i = 2; i * i <= q; i++) {
            while(q % i == 0) {
                if(pc < 2) {
                    mv1 *= i;
                }
                ++pc;
                q /= i;
            }
        }
        if(q > 1) {
            if(pc < 2) {
                mv1 *= q;
            }
            pc++, q = 1;
        }
        if(pc == 2) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl << mv1 << endl;
        }
    }
}