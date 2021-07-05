#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

using namespace std;

int t, n, b, res, nxt[21][21][21][21][10];
ll p;
ld dp[21][21][21][21];

int main() {
    cin >> t >> n >> b >> p;
    for(int full = n; full>=0; full--) {
        for(int one = n-full; one>=0; one--) {
            for(int two = n-full-one; two>=0; two--) {
                for(int rem = b-3; rem>=0; rem--) {
                    for(int dig = 0; dig<10; dig++) {
                        ld best = 0;
                        if(one>0) {
                            ld tmp = dp[full+1][one-1][two][rem]+0.1*dig;
                            if(tmp>=best) {
                                best = tmp;
                                nxt[full][one][two][rem][dig] = 0;
                            }
                        }
                        if(two>0) {
                            ld tmp = dp[full][one+1][two-1][rem]+0.01*dig;
                            if(tmp>=best) {
                                best = tmp;
                                nxt[full][one][two][rem][dig] = 1;
                            }
                        }
                        if(full+one+two<n) {
                            if(rem==b-3) {
                                ld tmp = dp[full][one][two+1][0]+0.001*dig;
                                if(tmp>=best) {
                                    best = tmp;
                                    nxt[full][one][two][rem][dig] = 2;
                                }
                            } else {
                                ld tmp = dp[full][one][two][rem+1];
                                if(tmp>=best) {
                                    best = tmp;
                                    nxt[full][one][two][rem][dig] = 3;
                                }
                            }
                        }
                        dp[full][one][two][rem]+=(best/10);
                    }
                }
            }
        }
    }
    while(t--) {
        int full = 0, one = 0, two = 0, rem = 0;
        for(int i = 0, d; i<n*b; i++) {
            cin >> d;
            int loc;
            if(nxt[full][one][two][rem][d]==0) {
                loc = full+1;
                ++full, --one;
            } else if(nxt[full][one][two][rem][d]==1) {
                loc = full+one+1;
                ++one, --two;
            } else if(nxt[full][one][two][rem][d]==2) {
                loc = full+one+two+1;
                ++two, rem = 0;
            } else {
                loc = full+one+two+1;
                ++rem;
            }
            cout << loc << endl;
        }
    }
    cin >> res;
}
