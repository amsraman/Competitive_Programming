#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, k, a, b, c, e[1000000];
ll dp[1000000], mx1, mx2, num1[1000000], num2[1000000], sz1[1000000], sz2[1000000], tot1, tot2, ans1, ans2;
vector<int> g[1000000], reg;
string s;

int add(int x, int y, int md)
{
    return (x+y)%md;
}

int mul(int x, int y, int md)
{
    return (ll(x)*ll(y))%md;
}

void dfs(int x, int p)
{
    dp[x] = 1;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs(g[x][i],x), dp[x]+=dp[g[x][i]];
    if(s[x]=='#')
        dp[x] = 0;
    else if((x==0)||(s[p]=='#'))
        reg.push_back(dp[x]), ans1+=(dp[x]*(dp[x]-1)/2);
}

void dfs2(int x, int p)
{
    num1[x] = (dp[x]==mx1), num2[x] = ((dp[x]==mx2)&&(s[p]=='#'));
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs2(g[x][i],x), num1[x]+=num1[g[x][i]], num2[x]+=num2[g[x][i]];
    if((s[x]=='*')&&(s[p]=='*'))
        return;
    if((mx1>0)&&(mx2>0))
        ans2+=mx1*mx2*(num1[x]*(tot2-num2[x])+num2[x]*(tot1-num1[x]));
    else if(mx1>0)
        ans2+=mx1*mx1*num1[x]*(tot1-num1[x]);
}

void dfs3(int x, int p)
{
    sz1[x] = 1, sz2[x] = (s[x]=='*');
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs3(g[x][i],x), sz1[x]+=sz1[g[x][i]], sz2[x]+=sz2[g[x][i]];
    if((s[x]=='*')&&(s[p]=='*'))
        ans2+=(reg[0]-sz2[x])*sz2[x];
    else
        ans2+=(n-sz1[x])*sz1[x];
}

int main()
{
    freopen("quarantine_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k >> s;
        for(int i = 1; i<=k; i++)
            cin >> e[i];
        cin >> a >> b >> c;
        for(int i = k+1; i<n; i++)
            e[i] = 1+add(add(mul(a,e[i-2],i),mul(b,e[i-1],i),i),c,i);
        for(int i = 1; i<n; i++)
        {
            g[e[i]-1].push_back(i);
            g[i].push_back(e[i]-1);
        }
        dfs(0,0);
        sort(reg.begin(),reg.end());
        if(reg.size()>1)
            ans1+=(reg[reg.size()-1]*reg[reg.size()-2]);
        if((reg.size()>1)&&(reg[reg.size()-1]!=reg[reg.size()-2]))
            mx1 = reg[reg.size()-1], mx2 = reg[reg.size()-2];
        else if(reg.size()>0)
            mx1 = reg[reg.size()-1];
        for(int i = 0; i<reg.size(); i++)
            tot1+=(reg[i]==mx1), tot2+=(reg[i]==mx2);
        if(reg.size()<2)
            for(int i = 0; i<g[0].size(); i++)
                dfs3(g[0][i],0);
        else
            for(int i = 0; i<g[0].size(); i++)
                dfs2(g[0][i],0);
        cout << "Case #" << _ << ": " << ans1 << " " << ans2 << endl;
        ans1 = ans2 = tot1 = tot2 = 0, mx1 = mx2 = -1, reg.clear();
        for(int i = 0; i<n; i++)
            g[i].clear();
    }
}
