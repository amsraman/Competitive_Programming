#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("prime_subtractorization_input.txt");
    ofstream cout("out.txt");
    bitset<10000001> is_prime; is_prime.set();
    for(int i = 2; i <= 1e7; i++) {
        for(int j = 2 * i; j <= 1e7; j += i) {
            is_prime[j] = false;
        }
    }
    is_prime[0] = is_prime[1] = false;
    vector<int> ps(1e7 + 1, 0);
    for(int i = 2; i <= 1e7; i++) {
        ps[i] = ps[i - 1];
        if(is_prime[i] && is_prime[i - 2]) {
            ++ps[i];
        }
    }
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        int ans = ps[n];
        if(ans > 0) ++ans;
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}
/*
*/