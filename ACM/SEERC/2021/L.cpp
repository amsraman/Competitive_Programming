#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, tot[3];
pair<pair<int, int>, char> mv;
string s;
bool one;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    for(char c: s) {
        ++tot[c - 'A'];
    }
    for(int i = 0; i < 3; i++) {
        int extra = n - tot[i];
        if(extra <= 0) {
            continue;
        }
        array<int, 3> num = {0, 0, 0};
        for(int j = 0, k = 0; j < 3 * n; j++) {
            while(k < 3 * n && (k - j - num[i]) < extra) {
                ++num[s[k] - 'A'];
                ++k;
            }
            bool works = ((k - j - num[i]) == extra);
            for(int l = 0; l < 3; l++) {
                if(l != i) {
                    works &= ((tot[l] - num[l]) == n);
                }
            }
            if(works) {
                one = true;
                mv = {{j + 1, k}, 'A' + i};
            }
            --num[s[j] - 'A'];
        }
    }
    if(tot[0] == n && tot[1] == n) {
        cout << "0\n";
    } else if(one) {
        cout << "1\n" << mv.f.f << " " << mv.f.s << " " << mv.s << '\n';
    } else {
        tot[0] = tot[1] = tot[2] = 0;
        int cur = 0;
        for(; cur < 3 * n; cur++) {
            ++tot[s[cur] - 'A'];
            if(tot[s[cur] - 'A'] == n) {
                break;
            }
        }
        cout << "2\n";
        for(int i = 0; i < 3; i++) {
            if(tot[i] < n) {
                int extra = n - tot[i];
                cout << cur + 2 << " " << cur + extra + 1 << " " << char('A' + i) << '\n';
                cur += extra;
            }
        }
    }
}