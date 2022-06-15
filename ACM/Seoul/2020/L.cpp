#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, h[1000000];
ll ans;
vector<pair<ll,ll>> down, up;

void solve(int lb, int ub, int lo, int hi)
{
    int mid = (lb+ub)/2, opt = lo;
    ans = max(ans,(up[opt].s-down[mid].s)*(up[opt].f-down[mid].f));
    for(int i = lo; i<=hi; i++)
        if((up[i].s-down[mid].s)*(up[i].f-down[mid].f)>=(up[opt].s-down[mid].s)*(up[opt].f-down[mid].f))
            opt = i, ans = max(ans,(up[opt].s-down[mid].s)*(up[opt].f-down[mid].f));
    if(lb==ub)
        return;
    solve(lb,mid,lo,opt);
    solve(mid+1,ub,opt,hi);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> h[i];
    for(int i = 0; i<n; i++)
        if(down.empty()||down.back().s>-h[i])
            down.push_back({i,-h[i]});
    for(int i = 0; i<n; i++)
    {
        while(!up.empty()&&up.back().s<=h[i])
            up.pop_back();
        up.push_back({i,h[i]});
    }
    solve(0,down.size()-1,0,up.size()-1);
    cout << ans << '\n';
}