#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, a, b, c;
vector<pair<int,int> > g[100], cur;
bool found = true, v[100];

bool dfs(int x)
{
    if(v[x])
    {
        int ptr = cur.size()-2, minedge = g[cur[ptr+1].f][cur[ptr+1].s].s;
        while((ptr>-1)&&(g[cur[ptr].f][cur[ptr].s].f!=x))
            minedge = min(minedge,g[cur[ptr].f][cur[ptr].s].s), ptr--;
        ptr = cur.size()-1;
        while((ptr>-1)&&((g[cur[ptr].f][cur[ptr].s].f!=x)||(ptr==cur.size()-1)))
        {
            g[cur[ptr].f][cur[ptr].s].s-=minedge;
            if(!g[cur[ptr].f][cur[ptr].s].s)
                m--;
            ptr--;
        }
        return true;
    }
    v[x] = true;
    for(int i = 0; i<g[x].size(); i++)
    {
        cur.push_back({x,i});
        if((g[x][i].s!=0)&&(dfs(g[x][i].f)))
            return true;
        cur.pop_back();
    }
    v[x] = false;
    return false;
}

void reset()
{
    memset(v,false,sizeof(v));
    cur.clear();
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<m; i++)
    {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
    }
    while(found)
    {
        found = false;
        for(int i = 0; i<n; i++)
        {
            reset();
            if((!found)&&(dfs(i)))
                found = true;
        }
    }
    cout << m << endl;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<g[i].size(); j++)
            if(g[i][j].s!=0)
                cout << i << " " << g[i][j].f << " " << g[i][j].s << endl;
}
