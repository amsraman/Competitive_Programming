#include <bits/stdc++.h>

using namespace std;

int t, n, k, m, cur, c[2000001][26], cnt[2000001], ans;
string s;

void dfs(int x, int dep)
{
    for(int i = 0; i<26; i++)
        if(c[x][i])
            dfs(c[x][i],dep+1), cnt[x]+=cnt[c[x][i]];
    while(cnt[x]>=k)
        cnt[x]-=k, ans+=dep;
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n >> k;
        ans = m = 0;
        memset(c,0,sizeof(c));
        memset(cnt,0,sizeof(cnt));
        for(int i = 0; i<n; i++)
        {
            cin >> s;
            cur = 0;
            for(int j = 0; j<s.length(); j++)
            {
                if(!c[cur][(s[j]-'A')])
                    c[cur][(s[j]-'A')] = ++m;
                cur = c[cur][(s[j]-'A')];
            }
            cnt[cur]++;
        }
        dfs(0,0);
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
