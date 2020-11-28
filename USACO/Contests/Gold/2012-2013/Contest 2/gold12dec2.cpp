#include <bits/stdc++.h>

using namespace std;

int n, cur, tot, t[300001][26], state[30000][26];
string s[30000];
vector<int> g[30000][26];
vector<string> ans;
bool cyc, conn[30000][26][26], ep[300001];

void dfs(int x, int y)
{
    state[x][y] = 1;
    for(int i = 0; i<g[x][y].size(); i++)
    {
        cyc|=(state[x][g[x][y][i]]==1);
        if(!state[x][g[x][y][i]])
            dfs(x,g[x][y][i]);
    }
    state[x][y] = 2;
}

int main()
{
    freopen("first.in","r",stdin);
    freopen("first.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> s[i];
    for(int i = 0; i<n; i++)
    {
        cur = 0;
        for(int j = 0; j<s[i].length(); j++)
        {
            if(!t[cur][(s[i][j]-'a')])
                t[cur][(s[i][j]-'a')] = ++tot;
            cur = t[cur][(s[i][j]-'a')];
        }
        ep[cur] = true;
    }
    for(int i = 0; i<n; i++)
    {
        cyc = false, cur = 0;
        for(int j = 0; j<s[i].length(); j++)
        {
            for(int k = 0; k<26; k++)
                if((t[cur][k]!=0)&&((s[i][j]-'a')!=k))
                    if(!conn[i][(s[i][j]-'a')][k])
                        g[i][(s[i][j]-'a')].push_back(k), conn[i][(s[i][j]-'a')][k] = true;
            cyc|=ep[cur], cur = t[cur][(s[i][j]-'a')];
        }
        for(int j = 0; j<26; j++)
            if(!state[i][j])
                dfs(i,j);
        if(!cyc)
            ans.push_back(s[i]);
    }
    cout << ans.size() << endl;
    for(string str: ans)
            cout << str << endl;
}
