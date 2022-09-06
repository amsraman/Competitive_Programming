#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, grundy[100001], ans = INF;
vector<int> factors[200001];

int main() {
    cin >> n;
    for(int i = 2; i <= 2e5; i++) {
        for(int j = 2 * i; j <= 2e5; j += i) {
            factors[j].push_back(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        set<int> prv;
        for(int j: factors[2 * i]) {
            if(((2 * i / j) - (j - 1)) & 1 ^ 1) {
                int lo = ((2 * i / j) - (j - 1)) / 2, hi = lo + (j - 1);
                if(lo >= 1) {
                    prv.insert(grundy[hi] ^ grundy[lo - 1]);
                    if(i == n && grundy[lo - 1] == grundy[hi]) {
                        ans = min(ans, hi - lo + 1);
                    }
                }
            }
        }
        while(prv.count(grundy[i])) {
            ++grundy[i];
        }
        grundy[i] ^= grundy[i - 1];
    }
    cout << (ans == INF ? -1 : ans) << endl;
}