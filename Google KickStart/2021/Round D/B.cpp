#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, t;
ll c, ans;
pair<ll,ll> intervals[100000];
map<ll,int> inc;

int main() {
    cin >> t;
    for(int _ = 1; _<=t; _++) {
        cin >> n >> c;
        set<ll> events;
        for(int i = 0; i<n; i++) {
            cin >> intervals[i].f >> intervals[i].s;
            ++inc[intervals[i].f+1], --inc[intervals[i].s];
            events.insert(intervals[i].f+1); events.insert(intervals[i].s);
        }
        auto it = ++events.begin();
        vector<pair<ll,pair<ll,ll>>> best_cuts;
        int cur = 0;
        for(ll i: events) {
            if(it == events.end()) {
                break;
            }
            cur += inc[i];
            best_cuts.push_back({cur,{i,(*it)}});
            ++it;
        }
        sort(best_cuts.begin(),best_cuts.end());
        reverse(best_cuts.begin(),best_cuts.end());
        for(int i = 0; i<best_cuts.size(); i++) {
            ll cuts_possible = best_cuts[i].s.s - best_cuts[i].s.f;
            ans += min(c,cuts_possible) * best_cuts[i].f;
            c -= min(c,cuts_possible);
            if(c == 0) {
                break;
            }
        }
        cout << "Case #" << _ << ": " << ans + n << endl;
        events.clear();
        inc.clear();
        best_cuts.clear();
        ans = 0;
    }
}