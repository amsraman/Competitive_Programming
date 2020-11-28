#include <bits/stdc++.h>
#define INF 0xfffffffff
typedef long long ll;

using namespace std;

int n, w, wt[100], val[100];
ll dp[101][100001], ans;

int main()
{
  for(int i = 0; i<101; i++)
    for(int j = 0; j<100001; j++)
      dp[i][j] = -INF;
  cin >> n >> w;
  for(int i = 0; i<n; i++)
    cin >> wt[i] >> val[i];
  dp[0][0] = 0;
  for(int i = 0; i<n; i++)
    for(int j = 0; j<=w; j++)
    {
      dp[i+1][j] = max(dp[i+1][j],dp[i][j]);
      if(j+wt[i]<=w)
        dp[i+1][j+wt[i]] = max(dp[i+1][j+wt[i]],dp[i][j]+val[i]);
      ans = max(ans,dp[i+1][j]);
    }
  cout << ans << endl;
}
