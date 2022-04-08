#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

void pr_128(ll num) {
    if(num == 0) {
        cout << 0;
        return;
    }
    if(num < 0) {
        cout << '-';
        num *= -1;
    }
    vector<int> dig;
    while(num > 0) {
        dig.push_back(num % 10);
        num /= 10;
    }
    reverse(dig.begin(), dig.end());
    for(int d: dig) {
        cout << d;
    }
}

int t, n, q, grade[3];
ll fact[31], ncr[121][121];
string ans[3];

int main() {
    fact[0] = ncr[0][0] = 1;
    for(int i = 1; i <= 120; i++) {
        fact[i] = fact[i - 1] * i;
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
        }
    }
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> q;
        for(int i = 0; i < n; i++) {
            cin >> ans[i] >> grade[i];
        }
        cout << "Case #" << _ << ": ";
        if(n == 1) {
            if(grade[0] > q - grade[0]) {
                cout << ans[0] << " " << grade[0] << "/1" << endl;
            } else {
                for(char c: ans[0]) {
                    cout << char(c ^ 'T' ^ 'F');
                }
                cout << " " << q - grade[0] << "/1" << endl;
            }
        } else if(n == 2) {
            if(grade[0] < q - grade[0]) {
                grade[0] = q - grade[0];
                for(int i = 0; i < q; i++) {
                    ans[0][i] ^= 'T' ^ 'F';
                }
            }
            if(grade[1] < q - grade[1]) {
                grade[1] = q - grade[1];
                for(int i = 0; i < q; i++) {
                    ans[1][i] ^= 'T' ^ 'F';
                }
            }
            if(grade[0] < grade[1]) {
                swap(ans[0], ans[1]);
                swap(grade[0], grade[1]);
            }
            cout << ans[0] << " " << grade[0] << "/1" << endl;
        } else {
            vector<vector<int>> types(2, vector<int>(2, 0));
            for(int i = 0; i < q; i++) {
                if(ans[0][i] == 'T') {
                    ++types[ans[1][i] == 'T'][ans[2][i] == 'T'];
                } else {
                    ++types[ans[1][i] == 'F'][ans[2][i] == 'F'];
                }
            }
            grade[1] -= (types[0][1] + types[0][0]);
            grade[2] -= (types[1][0] + types[0][0]);
            assert(abs(grade[0] % 2) == abs(grade[1] % 2));
            assert(abs(grade[0] % 2) == abs(grade[2] % 2));
            ll tot = 0;
            vector<vector<ll>> nums(2, vector<ll>(2, 0));
            for(int i = 0; i <= types[1][1]; i++) {
                grade[0] -= i, grade[1] -= i, grade[2] -= i;
                int j = (grade[0] + grade[1]) / 2, k = (grade[0] + grade[2]) / 2, l = (-grade[1] - grade[2]) / 2;
                if(min({i, j, k, l}) >= 0 && j <= types[1][0] && k <= types[0][1] && l <= types[0][0]) {
                    // what's the number of assignments for which this works?
                    // (types[1][1] choose i) * (types[1][0] choose j) * (types[0][1] choose k) * (types[0][0] choose l)
                    vector<vector<int>> places = {{l, k}, {j, i}};
                    ll pos = ncr[types[1][1]][i] * ncr[types[1][0]][j] * ncr[types[0][1]][k] * ncr[types[0][0]][l];
                    for(int t1 = 0; t1 < 2; t1++) {
                        for(int t2 = 0; t2 < 2; t2++) {
                            if(types[t1][t2] > 0 && places[t1][t2] > 0) {
                                pos /= ncr[types[t1][t2]][places[t1][t2]];
                                pos *= ncr[types[t1][t2] - 1][places[t1][t2] - 1];
                                nums[t1][t2] += pos;
                                pos /= ncr[types[t1][t2] - 1][places[t1][t2] - 1];
                                pos *= ncr[types[t1][t2]][places[t1][t2]];
                            }
                        }
                    }
                    tot += pos;
                }
                grade[0] += i, grade[1] += i, grade[2] += i;
            }
            vector<vector<vector<char>>> go(2, vector<vector<char>>(2, vector<char>(2)));
            ll num = 0;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    if(nums[i][j] >= tot - nums[i][j]) {
                        num += nums[i][j] * types[i][j];
                        go[1][i][j] = 'T';
                        go[0][i ^ 1][j ^ 1] = 'F';
                    } else {
                        num += (tot - nums[i][j]) * types[i][j];
                        go[1][i][j] = 'F';
                        go[0][i ^ 1][j ^ 1] = 'T';
                    }
                }
            }
            for(int i = 0; i < q; i++) {
                cout << go[ans[0][i] == 'T'][ans[1][i] == 'T'][ans[2][i] == 'T'];
            }
            cout << " ";
            ll g = __gcd(num, tot);
            num /= g, tot /= g;
            pr_128(num);
            cout << "/";
            pr_128(tot);
            cout << endl;
        }
    }
}