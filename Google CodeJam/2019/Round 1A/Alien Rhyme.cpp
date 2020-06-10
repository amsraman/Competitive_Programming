#include <bits/stdc++.h>

using namespace std;

int t, n, m, c[50001][26], cnt[50001];
string w;

void dfs(int x)
{
    for(int i = 0; i<26; i++)
        if(c[x][i])
            dfs(c[x][i]), cnt[x]+=cnt[c[x][i]];
    if((cnt[x]>=2)&&(x!=0))
        cnt[x]-=2;
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        memset(c,0,sizeof(c));
        memset(cnt,0,sizeof(cnt));
        m = 0;
        cin >> n;
        for(int i = 0; i<n; i++)
        {
            cin >> w;
            int cur = 0;
            for(int j = w.length()-1; j>=0; j--)
            {
                if(!c[cur][(w[j]-'A')])
                    c[cur][(w[j]-'A')] = ++m;
                cur = c[cur][(w[j]-'A')];
            }
            cnt[cur]++;
        }
        dfs(0);
        cout << "Case #" << cs+1 << ": " << n-cnt[0] << endl;
    }
}
