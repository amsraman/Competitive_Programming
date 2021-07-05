#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll ans;
vector<ll> adj[500000];

int main()
{
    cin >> n;
    for(int i = 0, u, v, p; i<n-1; i++)
    {
        cin >> u >> v >> p;
        adj[u].push_back(p);
        adj[v].push_back(p);
    }
    for(int i = 0; i<n; i++)
    {
        ll tot = 0, mx = 0;
        for(ll j: adj[i])
            tot+=j, mx = max(mx,j);
        if(2*mx>tot)
            ans+=2*mx-tot;
        else
            ans+=(tot%2);
    }
    cout << ans/2 << endl;
}