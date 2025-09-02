#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n), b(n); int num_odds = 0, num_evens = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            num_odds += a[i] % 2;
            num_evens += 1 - (a[i] % 2);
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        bool res = true, ev = false; int sw = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] % 2 == b[i] % 2) {
                if(a[i] > b[i]) res = false;
                if(a[i] < b[i]) ev = true;
            } else {
                ++sw;
            }
        }
        if(num_odds % 2 == 1) {
            if(sw > 1) res = false;
        } else if(sw > 0) {
            res = false;
        }
        bool will_sw = (sw > 0 && num_odds % 2 == 1);
        if(ev && num_evens % 2 == 1 && !will_sw) {
            res = false;
        }
        cout << (res ? "YES" : "NO") << '\n';
    }
}
/*
Move 1 keeps the state the same
Move 2 makes the state opposite

So it's like. if I am my correct parity, make me the correct thing. Then never touch me again

Otherwise, I need to be flipped at some point. Operation 2 can only be used once right.
*/