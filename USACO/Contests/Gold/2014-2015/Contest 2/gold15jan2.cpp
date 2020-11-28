#include <bits/stdc++.h>

using namespace std;

int n, l, d[20], c[20], st[20][1000], sz[(1<<20)], dp[(1<<20)], ans = 21;

int main()
{
    freopen("movie.in","r",stdin);
    freopen("movie.out","w",stdout);
    cin >> n >> l;
    for(int i = 0; i<n; i++)
    {
        cin >> d[i] >> c[i];
        for(int j = 0; j<c[i]; j++)
            cin >> st[i][j];
    }
    for(int i = 1; i<(1<<n); i++)
        sz[i] = sz[i-(i&(-i))]+1;
    for(int i = 0; i<(1<<n); i++)
        for(int j = 0; j<n; j++)
            if(!((1<<j)&i))
            {
                int l = 0, g = c[j]-1;
                while(l<g)
                {
                    int mid = (l+g+1)/2;
                    if(st[j][mid]>dp[i]) g = mid-1;
                    else l = mid;
                }
                if((st[j][g]<=dp[i])&&(st[j][g]+d[j]>dp[i+(1<<j)]))
                    dp[i+(1<<j)] = st[j][g]+d[j];
            }
    for(int i = 0; i<(1<<n); i++)
        if(dp[i]>=l)
            ans = min(ans,sz[i]);
    cout << ((ans==21)?(-1):(ans)) << endl;
}
