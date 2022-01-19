#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll l, r, k, p, num[1000000], fd[1000000], ans;
vector<int> primes;
bool comp[4000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int i = 2; i <= 4e6; i++) {
        if(comp[i]) {
            continue;
        }
        primes.push_back(i);
        for(int j = 2 * i; j <= 4e6; j += i) {
            comp[j] = true;
        }
    }
    while(t--) {
        cin >> l >> r >> k >> p;
        int dif = r - l + 1;
        for(int i = 0; i < dif; i++) {
            num[i] = l + i;
            fd[i] = 1;
        }
        for(int pr: primes) {
            if(pr > r) {
                break;
            }
            ll starting_pos = pr + ((l - 1) / pr) * pr;
            for(ll i = starting_pos; i <= r; i += pr) {
                ll pw = 1;
                while(num[i - l] % pr == 0) {
                    num[i - l] /= pr, pw *= pr;
                }
                if(pr % 4 == 1) {
                    fd[i - l] *= pw;
                } else if(pr % 4 == 3) {
                    fd[i - l] *= (pw + 2 * (pw - 1) / (pr - 1));
                }
            }
        }
        for(int i = 0; i < dif; i++) {
            if(num[i] > 1) {
                if(num[i] % 4 == 1) {
                    fd[i] *= num[i];
                } else if(num[i] % 4 == 3) {
                    fd[i] *= (num[i] + 2);
                }
            }
            fd[i] *= 6;
        }
        ans = 0;
        for(int i = 0; i < dif; i++) {
            ans = (ans + (fd[i] ^ k)) % p;
        }
        cout << ans << '\n';
    }
}
