#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long ll;
#define f first
#define s second

using namespace __gnu_pbds;
using namespace std;

int n, t, prev_x, prev_y;
ll ans;
vector<pair<pair<int,int>,pair<int,int>>> h_segs, v_segs;
tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> bit[200000][2];

int between(int ind, int pf, int b1, int b2) {
    int ind1 = bit[pf][ind].order_of_key({b1,-1});
    int ind2 = bit[pf][ind].order_of_key({b2+1,-1});
    return ind2-ind1;
}

ll qry(int ind, int pf, int b1, int b2) {
    ll ret = 0;
    for(pf++; pf>0; pf-=(pf&(-pf))) {
        ret+=between(ind,pf-1,b1,b2);
    }
    return ret;
}

void upd(int ind, int pf, pair<int,int> val, bool ins) {
    for(pf++; pf<=2*n; pf+=(pf&(-pf))) {
        if(ins) {
            bit[pf-1][ind].insert(val);
        } else {
            bit[pf-1][ind].erase(val);
        }
    }
}

int main() {
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");
    cin >> n >> t >> prev_x >> prev_y;
    for(int i = 1, x, y; i<n; i++) {
        cin >> x >> y;
        if(x==prev_x) {
            v_segs.push_back({{x,i},{min(y,prev_y)+1,max(y,prev_y)-1}});
        } else {
            h_segs.push_back({{min(x,prev_x),1},{y,i}});
            h_segs.push_back({{max(x,prev_x),0},{y,i}});
        }
        prev_x = x, prev_y = y;
    }
    sort(h_segs.begin(),h_segs.end());
    sort(v_segs.begin(),v_segs.end());
    for(int i = 0, ptr = 0; i<v_segs.size(); i++) {
        while(ptr<h_segs.size()&&(h_segs[ptr].f.f+h_segs[ptr].f.s)<=v_segs[i].f.f) {
            upd(0,h_segs[ptr].s.s,{h_segs[ptr].s.f,h_segs[ptr].s.s},h_segs[ptr].f.s);
            upd(1,h_segs[ptr].s.s+t-1,{h_segs[ptr].s.f,h_segs[ptr].s.s},h_segs[ptr].f.s);
            ++ptr;
        }
        ans+=(qry(0,2*n-1,v_segs[i].s.f,v_segs[i].s.s)-qry(0,v_segs[i].f.s+t-1,v_segs[i].s.f,v_segs[i].s.s)+qry(1,v_segs[i].f.s-1,v_segs[i].s.f,v_segs[i].s.s));
    }
    cout << ans << endl;
}