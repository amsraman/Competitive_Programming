#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, k, tiles[50][50], dp[50][50], ans = 0x3f3f3f3f;
vector<pair<int,int>> pos[2500];

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> tiles[i][j];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            pos[tiles[i][j]-1].push_back({i,j});
    memset(dp,0x3f3f3f3f,sizeof(dp));
    for(int j = 0; j<pos[0].size(); j++)
        dp[pos[0][j].f][pos[0][j].s] = 0;
    for(int i = 1; i<k; i++)
        for(int j = 0; j<pos[i].size(); j++)
            for(int pv = 0; pv<pos[i-1].size(); pv++)
                dp[pos[i][j].f][pos[i][j].s] = min(dp[pos[i][j].f][pos[i][j].s],dp[pos[i-1][pv].f][pos[i-1][pv].s]+abs(pos[i][j].f-pos[i-1][pv].f)+abs(pos[i][j].s-pos[i-1][pv].s));
    for(int i = 0; i<pos[k-1].size(); i++)
        ans = min(ans,dp[pos[k-1][i].f][pos[k-1][i].s]);
    cout << (ans==0x3f3f3f3f?-1:ans) << endl;
}
