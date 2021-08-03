#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int n, m, s, t, warehouse[2], employee_loc[100000], client_loc[100000];
ll dist[100000][2], employee_dist[100000][2], client_dist[100000][2], diff[100000], employee_dists, client_dists, ans = INF;
vector<pair<ll,int>> employee_starters;
vector<pair<int,ll>> g[100000];
bool vis[100000][2];

void dijkstra(int ind) {
    priority_queue<pair<ll,int>> q;
    q.push({0,warehouse[ind]});
    for(int i = 0; i<n; i++) {
        if(i != warehouse[ind]) {
            dist[i][ind] = INF;
        }
    }
    while(!q.empty()) {
        pair<ll,int> x = q.top(); q.pop();
        if(vis[x.s][ind]) {
            continue;
        }
        vis[x.s][ind] = true;
        for(pair<int,ll> e: g[x.s]) {
            if(!vis[e.f][ind] && dist[x.s][ind] + e.s < dist[e.f][ind]) {
                dist[e.f][ind] = dist[x.s][ind] + e.s;
                q.push({-dist[e.f][ind],e.f});
            }
        }
    }
}

int main() {
    cin >> n >> m >> s >> t >> warehouse[0] >> warehouse[1];
    --warehouse[0], --warehouse[1];
    for(int i = 0; i<s; i++) {
        cin >> employee_loc[i];
        --employee_loc[i];
    }
    for(int i = 0; i<t; i++) {
        cin >> client_loc[i];
        --client_loc[i];
    }
    for(int i = 0, u, v, d; i<m; i++) {
        cin >> u >> v >> d;
        g[u-1].push_back({v-1,d});
        g[v-1].push_back({u-1,d});
    }
    dijkstra(0), dijkstra(1);
    for(int i = 0; i<s; i++) {
        employee_dist[i][0] = dist[employee_loc[i]][0];
        employee_dist[i][1] = dist[employee_loc[i]][1];
        employee_starters.push_back({employee_dist[i][0], i});
    }
    for(int i = 0; i<t; i++) {
        client_dist[i][0] = dist[client_loc[i]][0];
        client_dist[i][1] = dist[client_loc[i]][1];
        diff[i] = client_dist[i][1] - client_dist[i][0];
        client_dists += client_dist[i][0];
    }
    sort(employee_starters.begin(),employee_starters.end());
    sort(diff,diff+t);
    set<pair<ll,int>> max_dist_in, min_diff_in, min_dist_out;
    for(int i = 0; i<s; i++) {
        if(i < t) {
            employee_dists += employee_starters[i].f;
            max_dist_in.insert(employee_starters[i]);
            min_diff_in.insert({employee_dist[employee_starters[i].s][1] - employee_starters[i].f, employee_starters[i].s});
        } else {
            min_dist_out.insert({employee_dist[employee_starters[i].s][1], employee_starters[i].s});
        }
    }
    ans = employee_dists + client_dists;
    for(int i = 0; i<t; i++) {
        // iterate over number of movements through warehouse[0]
        client_dists += diff[i];
        if(min_dist_out.empty() || ((min_diff_in.begin() -> f) < ((min_dist_out.begin() -> f) - ((--max_dist_in.end()) -> f)))) {
            employee_dists += (min_diff_in.begin() -> f);
            int to_add = min_diff_in.begin() -> s;
            min_diff_in.erase(min_diff_in.begin());
            max_dist_in.erase({employee_dist[to_add][0], to_add});
        } else {
            employee_dists += ((min_dist_out.begin() -> f) - ((--max_dist_in.end()) -> f));
            int to_rem = (--max_dist_in.end()) -> s, to_add = min_dist_out.begin() -> s;
            max_dist_in.erase(--max_dist_in.end());
            min_diff_in.erase({employee_dist[to_rem][1] - employee_dist[to_rem][0], to_rem});
            min_dist_out.insert({employee_dist[to_rem][1], to_rem});
            min_dist_out.erase({employee_dist[to_add][1], to_add});
        }
        ans = min(ans, employee_dists + client_dists);
    }
    cout << ans << endl;
}