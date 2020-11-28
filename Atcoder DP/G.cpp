#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, state[100000], dp[100000], ans;
vector<int> g[100000], top;

void dfs(int a)
{
  if(state[a]==2)
    return;
  state[a] = 1;
  for(int i = 0; i<g[a].size(); i++)
    dfs(g[a][i]);
  state[a] = 2;
  top.push_back(a);
}

int main()
{
  cin >> n >> m;
  for(int i = 0; i<m; i++)
  {
    cin >> x >> y;
    g[x-1].push_back(y-1);
  }
  for(int i = 0; i<n; i++)
    if(!state[i])
      dfs(i);
  for(int i = n-1; i>=0; i--)
    for(int j = 0; j<g[top[i]].size(); j++)
      dp[g[top[i]][j]] = max(dp[g[top[i]][j]],dp[top[i]]+1);
  for(int i = 0; i<n; i++)
    ans = max(ans,dp[i]);
  cout << ans << endl;
}
