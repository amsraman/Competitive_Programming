#include <bits/stdc++.h>

using namespace std;

int n, k, cur, lp[100001], dp[100000][101][2];
pair<int,int> in[100001];
vector<pair<int,int> > ar;

int main()
{
    freopen("lifeguards.in","r",stdin);
    freopen("lifeguards.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++) cin >> in[i].first >> in[i].second;
    sort(in,in+n);
    for(int i = 0; i<n; i++)
    {
        if(((i==0)||(in[i].second>=in[i-1].second))&&((i==n-1)||((in[i].first!=in[i+1].first)||(in[i].second==in[i+1].second))))
        {
            ar.push_back(in[i]);
        }
    }
    k-=(n-ar.size()), n = ar.size();
    for(int i = 0; i<n; i++)
    {
        while(ar[cur].second<ar[i].first) cur++;
        lp[i] = cur;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=min(i,k); j++)
        {
            if(i!=0) dp[i][j][0] = max(dp[i-1][j-1][0],dp[i-1][j-1][1]);
            if(i>=j) dp[i][j][1] = (ar[i].second-ar[i].first);
            cur = ((lp[i]==0) ? 0:max(dp[lp[i]-1][j-(i-lp[i])][0],dp[lp[i]-1][max(0,j-(i-lp[i]))][1]));
            if(lp[i]||(i>=j)) dp[i][j][1] = max(dp[i][j][1],cur+(ar[i].second-ar[i].first));
            dp[i][j][1] = max(dp[i][j][1],dp[lp[i]][max(0,j-(i-lp[i]-1))][1]+(ar[i].second-ar[lp[i]].second));
        }
    }
    cout << max(dp[n-1][k][0],dp[n-1][k][1]) << endl;
}
