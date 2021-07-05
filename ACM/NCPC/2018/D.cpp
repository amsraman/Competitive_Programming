#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second
#define INF 0xfffffffffffffff

using namespace std;

int n, m, k;
ll dist[1001][1001], dp[1001];
vector<pair<int,ll>> g[1000];
ll orders[1000][3];
bool vis[1000], doable[1001];

void dijkstra(int ind)
{
    priority_queue<pair<int,int>> q;
    for(int i = 0; i<n; i++)
        vis[i] = false, dist[ind][i] = INF;
    dist[ind][ind] = 0, q.push({0,ind});
    while(!q.empty())
    {
        int x = q.top().s;
        q.pop();
        if(vis[x])
            continue;
        vis[x] = true;
        for(pair<int,int> i: g[x])
            if(!vis[i.f]&&dist[ind][x]+i.s<dist[ind][i.f])
                dist[ind][i.f] = dist[ind][x]+i.s, q.push({-dist[ind][i.f],i.f});
    }
}

bool ok(ll x)
{
    for(int i = 1; i<=k; i++)
        doable[i] = false;
    doable[0] = true;
    //dp[i] = minimum time at which you finish delivering the first i pizzas, assuming you depart right after receiving the i^{th} pizza
    //because, greedily, you always want to finish delivering pizzas as early as possible
    //dp[i] = min_1..i-1 max(dp[j],time[i]) + total travel time from j -> i assuming doable[j] and everything from j->i is delivered in a reasonable amount of time
    //doable[i] is true if some j exists
    //ok hard part is verifying that second constraint.... 
    for(int i = 1; i<=k; i++)
    {
        ll trav_time = 0, mx = 0, pv_trav_time;
        dp[i] = INF;
        for(int j = i-1; j>=0; j--)
        {
            if(j==i-1)
                trav_time = dist[0][orders[j][1]-1];
            else
                trav_time+=(dist[0][orders[j][1]-1]+dist[orders[j][1]-1][orders[j+1][1]-1]-dist[0][orders[j+1][1]-1]);
            if(j<i-1)
                mx+=(trav_time-pv_trav_time-(max(dp[j+1],orders[i-1][2])-max(dp[j],orders[i-1][2])));
            else
                mx = max(dp[j],orders[j][2])+trav_time-orders[j][0];
            mx = max(mx,max(dp[j],orders[i-1][2])+dist[orders[j][1]-1][0]-orders[j][0]);
            if(mx<=x&&doable[j])
                dp[i] = min(dp[i],max(dp[j],orders[i-1][2])+trav_time+dist[orders[i-1][1]-1][0]), doable[i] = true;
            pv_trav_time = trav_time;
        }
    }
    return doable[k];
}

int main()
{
    cin >> n >> m;
    for(int i = 0, u, v, d; i<m; i++)
    {
        cin >> u >> v >> d;
        g[u-1].push_back({v-1,d});
        g[v-1].push_back({u-1,d});
    }
    for(int i = 0; i<n; i++)
        dijkstra(i);
    cin >> k;
    for(int i = 0; i<k; i++)
        cin >> orders[i][0] >> orders[i][1] >> orders[i][2];
    ll lb = 0, ub = 1e18;
    while(lb<ub)
    {
        ll mid = (lb+ub)/2;
        if(ok(mid))
            ub = mid;
        else
            lb = mid+1;
    }
    cout << ub << endl;
}