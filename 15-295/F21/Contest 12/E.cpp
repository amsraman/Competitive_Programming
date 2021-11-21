#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, num_primes, prime[1000001], composite[1000001];
ll num[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int i = 1; i <= 1e6; i++) {
        for(int j = 2 * i; j <= 1e6; j += i) {
            num[j] += i;
        }
    }
    while(t--) {
        int n;
        cin >> n;
        if(num[n] < n) {
            cout << "deficient\n";
        } else if(num[n] == n) {
            cout << "perfect\n";
        } else {
            cout << "abundant\n";
        }
    }
}