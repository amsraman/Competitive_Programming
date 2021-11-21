#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

ll n, x, u, v, t, y, z, a[302];
ll d[300][300][2], dp[302][300];

int main()
{
    cin >> n >> x;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            d[i][j][0] = d[i][j][1] = INF;
    for(int i = 0; i<n; i++) d[i][i][0] = d[i][i][1] = 0;
    for(int i = 0; i<x; i++)
    {
        cin >> u >> v >> t;
        d[u][v][1] = d[v][u][1] = t;
    }
    cin >> y;
    for(int i = 0; i<y; i++)
    {
        cin >> u >> v >> t;
        d[u][v][0] = d[v][u][0] = t;
    }
    cin >> z;
    for(int i = 0; i<z; i++)
    {
        cin >> a[i+1];
    }
    for(int k = 0; k<n; k++)
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                d[i][j][0] = min(d[i][j][0],d[i][k][0]+d[k][j][0]);
                d[i][j][1] = min(d[i][j][1],d[i][k][1]+d[k][j][1]);
            }
        }
    }
    for(int i = 0; i<z+2; i++)
        for(int j = 0; j<n; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;
    for(int i = 1; i<=z+1; i++)
    {
        for(int j = 0; j<n; j++)
        {
            for(int k = 0; k<n; k++)
            {
                if(j!=k) dp[i][j] = min(dp[i][j],dp[i-1][k]+d[a[i-1]][k][0]+d[k][j][1]+d[j][a[i]][0]);
                else dp[i][j] = min(dp[i][j],dp[i-1][k]+d[a[i-1]][a[i]][0]);
            }
        }
    }
    cout << dp[z+1][0] << endl;
}
