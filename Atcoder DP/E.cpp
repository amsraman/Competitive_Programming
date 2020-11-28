#include <bits/stdc++.h>
#define INF 0xfffffffff
typedef long long ll;

using namespace std;

int n, w, wt[100], val[100], ans;
ll dp[101][100001];

int main()
{
  for(int i = 0; i<101; i++)
    for(int j = 0; j<100001; j++)
      dp[i][j] = INF;
  cin >> n >> w;
  for(int i = 0; i<n; i++)
    cin >> wt[i] >> val[i];
  dp[0][0] = 0;
  for(int i = 0; i<n; i++)
    for(int j = 0; j<=100000; j++)
    {
      dp[i+1][j] = min(dp[i+1][j],dp[i][j]);
      if(j+val[i]<=100000)
        dp[i+1][j+val[i]] = min(dp[i+1][j+val[i]],dp[i][j]+wt[i]);
      if(dp[i+1][j]<=w)
        ans = max(ans,j);
    }
  cout << ans << endl;
}
