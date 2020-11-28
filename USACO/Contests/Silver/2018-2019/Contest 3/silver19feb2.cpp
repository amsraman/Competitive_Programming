#include <bits/stdc++.h>

using namespace std;

int n, k, a, b, c, d, pre[1001][1001], ans;

int main()
{
    freopen("paintbarn.in","r",stdin);
    freopen("paintbarn.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
    {
        cin >> a >> b >> c >> d;
        pre[a][b]++, pre[c][b]--, pre[a][d]--, pre[c][d]++;
    }
    for(int i = 0; i<1001; i++)
        for(int j = 0; j<1001; j++)
        {
            if(i) pre[i][j]+=pre[i-1][j];
            if(j) pre[i][j]+=pre[i][j-1];
            if(i&&j) pre[i][j]-=pre[i-1][j-1];
            if(pre[i][j]==k) ans++;
        }
    cout << ans << endl;
}
