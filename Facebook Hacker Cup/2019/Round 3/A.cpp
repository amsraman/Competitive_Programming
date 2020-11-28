#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, h, n, c[4000][4000], dp[4001];
pair<int,int> lasers[4000];

int main()
{
    freopen("light_show_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> h >> n;
        for(int i = 0; i<n; i++)
            cin >> lasers[i].f >> lasers[i].s;
        sort(lasers,lasers+n);
        for(int i = 0; i<n; i++)
        {
            c[i][i] = lasers[i].s-1;
            for(int j = i+1; j<n; j++)
                c[i][j] = c[i][j-1]+lasers[j].s-1;
        }
        for(int i = 0; i<n; i++)
            for(int j = i; j<n; j++)
                c[i][j] = max(c[i][j],j-i+1-c[i][j]);
        memset(dp,0,sizeof(dp));
        for(int i = 1; i<=n; i++)
            for(int j = 0; j<i; j++)
                dp[i] = max(dp[i],dp[j]+c[j][i-1]*(c[j][i-1]-1)/2);
        cout << "Case #" << _ << ": " << dp[n] << endl;
    }
}
