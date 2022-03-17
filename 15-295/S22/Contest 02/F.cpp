#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n;
ll ans;
pair<int, int> v[200000];
vector<int> vc[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        ans = 0;
        for(int i = 0; i < n; i++) {
            cin >> v[i].f >> v[i].s;
            vc[v[i].f].push_back(v[i].s);
        }
        int tot = n, taken = 0;
        multiset<int> ms;
        for(int i = n; i >= 0; i--) {
            tot -= vc[i].size();
            for(int j: vc[i]) {
                ms.insert(j);
            }
            while(tot + taken < i) {
                ans += *ms.begin();
                ms.erase(ms.begin());
                ++taken;
            }
        }
        cout << ans << '\n';
        for(int i = 0; i <= n; i++) {
            vc[i].clear();
        }
    }
}