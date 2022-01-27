#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, a[100000], sz, works;
map<pair<int, int>, int> mp;
map<int, int> nd, overall;
ll ans = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    set<int> divs;
    int tmp = k;
    for(int i = 2; i * i <= k; i++) {
        int cnt = 0;
        while(tmp % i == 0) {
            ++cnt;
            tmp /= i;
        }
        if(cnt > 0) {
            nd[i] = cnt;
            divs.insert(i);
        }
    }
    if(tmp > 1) { 
        nd[tmp] = 1;
        divs.insert(tmp);
    }
    sz = divs.size();
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int tmp = a[i];
        for(int d: divs) {
            int cnt = 0;
            while(tmp % d == 0) {
                ++cnt, tmp /= d;
            }
            mp[{i, d}] = cnt;
            if(tmp == 1) {
                break;
            }
        }
    }
    for(int i = 0, j = 0; i < n; i++) {
        while(j < n && works < sz) {
            for(int d: divs) {
                int hi = mp[{j, d}], cur = overall[d], ned = nd[d];
                if(cur < ned && cur + hi >= ned) {
                    ++works;
                }
                overall[d] += hi;
            }
            ++j;
        }
        j = max(i + 1, j);
        if(works == sz) {
            ans += n - j + 1;
        }
        for(int d: divs) {
            int hi = mp[{i, d}], cur = overall[d], ned = nd[d];
            if(cur >= ned && cur - hi < ned) {
                --works;
            }
            overall[d] -= hi;
        }
    }
    cout << ans << '\n';
}