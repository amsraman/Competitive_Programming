#include <bits/stdc++.h>

using namespace std;

int n, h[100000], dp[100000];

int main()
{
  cin >> n;
  for(int i = 0; i<n; i++)
    cin >> h[i];
  for(int i = 1; i<n; i++)
    dp[i] = min(dp[i-1]+abs(h[i]-h[i-1]),dp[max(0,i-2)]+abs(h[i]-h[max(0,i-2)]));
  cout << dp[n-1] << endl;
}
