#include <bits/stdc++.h>

using namespace std;

int n, k, h[100000], dp[100000];

int main()
{
  memset(dp,0x3f3f3f3f,sizeof(dp));
  dp[0] = 0;
  cin >> n >> k;
  for(int i = 0; i<n; i++)
    cin >> h[i];
  for(int i = 1; i<n; i++)
    for(int j = 1; j<=min(i,k); j++)
      dp[i] = min(dp[i],dp[i-j]+abs(h[i]-h[i-j]));
  cout << dp[n-1] << endl;
}
