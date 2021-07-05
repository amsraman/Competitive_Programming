#include <bits/stdc++.h>

using namespace std;

int n, lc, tot, ans;
string input;
vector<int> un[100], g[100][2], st;
map<string,int> ind;
bool vis[100][2];

void dfs(int a, int b)
{
    vis[a][b] = true;
    if(b)
        ++tot;
    for(int i = 0; i<g[a][b].size(); i++)
        if(!vis[g[a][b][i]][b])
            dfs(g[a][b][i],b);
    if(!b)
        st.push_back(a);
}

int main()
{
    cin >> n;
    cin.ignore();
    for(int i = 0; i<n; i++)
    {
        getline(cin,input);
        input+=" ";
        vector<string> tmp;
        while(input.length()>1)
        {
            int sp = 0;
            while(sp<input.length()&&input[sp]!=' ')
                ++sp;
            tmp.push_back(input.substr(0,sp));
            input = input.substr(sp+1,input.length()-sp-1);
        }
        for(int j = 1; j<tmp.size(); j++)
        {
            if(!ind.count(tmp[j]))
                ind[tmp[j]] = ++lc;
            un[i].push_back(ind[tmp[j]]);
        }
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(i!=j)
                for(int k: un[j])
                    if(k==un[i][0])
                        g[i][0].push_back(j), g[j][1].push_back(i);
    for(int i = 0; i<n; i++)
        if(!vis[i][0])
            dfs(i,0);
    for(int i = n-1; i>=0; i--)
        if(!vis[st[i]][1])
            tot = 0, dfs(st[i],1), ans = max(ans,tot);
    cout << n-ans << endl;
}