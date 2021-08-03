#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, dist[50][50][50][50];
pair<int,int> dir[4] = {{-1,0},{1,0},{0,-1},{0,1}};
pair<pair<int,int>,pair<int,int>> p1, p2;
string grid1[50], grid2[50];
bool vis[50][50][50][50];

bool ok(int x, int y, int z) {
    bool ret = (x >= 0 && x < n && y >= 0 && y < m);
    if(ret && z == 0) {
        ret &= (grid1[x][y] == '.');
    } else if(ret) {
        ret &= (grid2[x][y] == '.');
    }
    return ret;
}

pair<int,int> app(pair<int,int> d, pair<int,int> pos, int mp) {
    if(ok(pos.f+d.f,pos.s+d.s,mp)) {
        pos.f += d.f;
        pos.s += d.s;
    }
    return pos;
}

int main() {
    cin >> n >> m;
    cin >> p1.f.f >> p1.f.s >> p1.s.f >> p1.s.s;
    cin >> p2.f.f >> p2.f.s >> p2.s.f >> p2.s.s;
    --p1.f.f, --p1.f.s, --p1.s.f, --p1.s.s;
    --p2.f.f, --p2.f.s, --p2.s.f, --p2.s.s;
    for(int i = 0; i<n; i++) {
        cin >> grid1[i];
    }
    for(int i = 0; i<n; i++) {
        cin >> grid2[i];
    }
    queue<pair<pair<int,int>,pair<int,int>>> q;
    q.push(p1);
    vis[p1.f.f][p1.f.s][p1.s.f][p1.s.s] = true;
    while(!q.empty()) {
        auto x = q.front(); q.pop();
        for(auto d1: dir) {
            pair<pair<int,int>,pair<int,int>> nxt = {app(d1,x.f,0),app(d1,x.s,1)};
            if(!vis[nxt.f.f][nxt.f.s][nxt.s.f][nxt.s.s]) {
                q.push(nxt);
                dist[nxt.f.f][nxt.f.s][nxt.s.f][nxt.s.s] = dist[x.f.f][x.f.s][x.s.f][x.s.s] + 1;
                vis[nxt.f.f][nxt.f.s][nxt.s.f][nxt.s.s] = true;
            }
        }
    }
    cout << (!vis[p2.f.f][p2.f.s][p2.s.f][p2.s.s] ? -1 : dist[p2.f.f][p2.f.s][p2.s.f][p2.s.s]) << endl;
}
