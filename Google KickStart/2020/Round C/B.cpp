#include <bits/stdc++.h>

using namespace std;

int t, r, c, state[26];
string in[30];
bool con[26][26], here[26], vis[26], cyc;
vector<int> g[26];
string ans;

void dfs(int x)
{
    if(state[x]==2)
        return;
    state[x] = 1;
    for(int i = 0; i<g[x].size(); i++)
    {
        if(state[g[x][i]]==1)
            cyc = true;
        else
            dfs(g[x][i]);
    }
    state[x] = 2;
    ans+=char('A'+x);
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        memset(here,false,sizeof(here));
        memset(vis,false,sizeof(vis));
        memset(state,0,sizeof(state));
        memset(con,false,sizeof(con));
        ans = "", cyc = false;
        for(int i = 0; i<26; i++)
            g[i].clear();
        cin >> r >> c;
        for(int i = 0; i<r; i++)
            cin >> in[i];
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                here[in[i][j]-'A'] = true;
        for(int i = 0; i<r-1; i++)
            for(int j = 0; j<c; j++)
                if((!con[in[i][j]-'A'][in[i+1][j]-'A'])&&(in[i][j]!=in[i+1][j]))
                    g[in[i][j]-'A'].push_back(in[i+1][j]-'A'), con[in[i][j]-'A'][in[i+1][j]-'A'] = true;
        for(int i = 0; i<26; i++)
            if((!vis[i])&&(here[i]))
                dfs(i);
        cout << "Case #" << cs+1 << ": " << (cyc?("-1"):(ans)) << endl;
    }
}
