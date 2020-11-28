#include <bits/stdc++.h>

using namespace std;

int dp[3000][3000], p1, p2;
string s, t, ans;

int main()
{
  cin >> s >> t;
  for(int i = 0; i<s.length(); i++)
    for(int j = 0; j<t.length(); j++)
    {
      dp[i][j] = int(s[i]==t[j]);
      if(i)
        dp[i][j] = max(dp[i][j],dp[i-1][j]);
      if(j)
        dp[i][j] = max(dp[i][j],dp[i][j-1]);
      if((i&&j)&&(s[i]==t[j]))
        dp[i][j] = max(dp[i][j],dp[i-1][j-1]+1);
    }
  p1 = s.length()-1, p2 = t.length()-1;
  while(ans.length()<dp[s.length()-1][t.length()-1])
  {
    if(s[p1]==t[p2])
      ans = s[p1]+ans, p1--, p2--;
    else if(p1&&(!p2||(dp[p1-1][p2]>=dp[p1][p2-1])))
      p1--;
    else
      p2--;
  }
  cout << ans << endl;
}
