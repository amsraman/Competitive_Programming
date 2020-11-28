#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int h, w, dp[1000][1000];
char in[1000][1000];

int main()
{
  cin >> h >> w;
  for(int i = 0; i<h; i++)
    for(int j = 0; j<w; j++)
      cin >> in[i][j];
  for(int i = 0; i<h; i++)
    for(int j = 0; j<w; j++)
    {
      if(i)
        dp[i][j]+=dp[i-1][j];
      if(j)
        dp[i][j]+=dp[i][j-1];
      if(!i && !j)
        dp[i][j] = 1;
      if(in[i][j]=='#')
        dp[i][j] = 0;
      dp[i][j]%=MOD;
    }
  cout << dp[h-1][w-1] << endl;
}
