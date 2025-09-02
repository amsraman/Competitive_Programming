#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<ll> fib(47, 0); fib[1] = 1;
    for(int i = 2; i < 47; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    auto rev = [&](string s) {
        int len = (int) s.length(); string res = "";
        for(int i = 0; i < len; i++) {
            if(s[i] == '1') {
                res += (i > 1 && s[i - 2] == '0') ? '0' : '1';
            }
        }
        return res;
    };
    vector<ll> gaps; vector<string> p1, p2;
    vector<ll> new_gaps; vector<string> np1, np2;
    for(int i = 0; i < n; i += 2) {
        ll cur_gap = (i == 0 ? a[i] : (a[i] - a[i - 1])) - 1;
        gaps.push_back(cur_gap); p1.push_back("01"); p2.push_back("10");
    }
    n = (int) gaps.size();
    for(int j = 22; j > 0; j--) {
        string c1 = "", c2 = "";
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                new_gaps.push_back(gaps[i]);
                c1 = p1[i], c2 = p2[i];
                continue;
            }
            if(gaps[i] == 0) {
                c1 += p1[i], c2 += p2[i];
            } else if(gaps[i] == fib[2 * (22 - j) + 2]) {
                c1 += "0" + p1[i], c2 += "0" + p2[i];
            } else {
                np1.push_back(c1); np2.push_back(c2);
                c1 = p1[i], c2 = p2[i];
                new_gaps.push_back(gaps[i]);
            }
        }
        np1.push_back(c1); np2.push_back(c2);
        swap(gaps, new_gaps); swap(p1, np1); swap(p2, np2);
        new_gaps.clear(); np1.clear(); np2.clear();
        n = (int) gaps.size();
        for(int i = 0; i < n; i++) {
            gaps[i] -= fib[2 * (22 - j) + 2];
            if(i < n - 1) gaps[i + 1] -= fib[2 * (22 - j) + 3];
            p1[i] = rev("0" + p1[i] + "01");
            p2[i] = rev("0" + p2[i] + "01");
        }
    }
    string s = "", t = "";
    ll f1 = fib[46], f2 = fib[45];
    for(int i = 0; i < n; i++) {
        int num_zeros = 0;
        while((gaps[i] - f1 * num_zeros) % f2 != 0) ++num_zeros;
        for(int j = 0; j < num_zeros; j++) {
            s += "0", t += "0";
        }
        for(int j = 0; j < (gaps[i] - f1 * num_zeros) / f2; j++) {
            s += "1", t += "1";
        }
        s += p1[i], t += p2[i];
    }
    cout << s << '\n' << t << '\n';
}
/*
01001 -> (?01) (001)
10010 -> (?1) (001) (0?)

0 -> 001 -> 00100101 -> 001001010010010100101

1 -> 3 -> 8 -> 21

01 -> 0(01)01 -> 0010(01)0100101 -> 001001010010(01)01001010010010100101
10 -> 0(10)01 -> 0010(10)0100101 -> 001001010010(10)01001010010010100101

(0, 0) -> (1, 2) -> (4, 7) -> (12, 20)

(x, y) -> (2x + y, x + y) -> (5x + 3y, 3x + 2y) -> (13x + 8y, 8x + 5y)
x + y -> 3x + 2y -> 8x + 5y -> 21x + 13y
*/