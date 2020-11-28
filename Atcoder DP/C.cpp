#include <bits/stdc++.h>

using namespace std;

int n, a[100000], b[100000], c[100000], dp[100000][3];

int main()
{
  cin >> n;
  for(int i = 0; i<n; i++)
    cin >> a[i] >> b[i] >> c[i];
  dp[0][0] = a[0], dp[0][1] = b[0], dp[0][2] = c[0];
  for(int i = 1; i<n; i++)
  {
    dp[i][0] = max(dp[i-1][1],dp[i-1][2])+a[i];
    dp[i][1] = max(dp[i-1][0],dp[i-1][2])+b[i];
    dp[i][2] = max(dp[i-1][0],dp[i-1][1])+c[i];
  }
  cout << max(max(dp[n-1][0],dp[n-1][1]),dp[n-1][2]) << endl;
}
