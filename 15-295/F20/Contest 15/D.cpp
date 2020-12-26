#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, dp[10001][10001], dist[1002][1002], best[1002], pv[1002];
pair<int,int> ind[1002];
string s, t, p[1002];
vector<string> points;

int edit(int x, int y)
{
    //idk do dp thing reeee
    for(int i = 0; i<=p[x].length(); i++)
        for(int j = 0; j<=p[y].length(); j++)
        {
            dp[i][j] = (i!=0 || j!=0)*0x3f3f3f3f;
            if(i>0)
                dp[i][j] = min(dp[i][j],dp[i-1][j]+1);
            if(j>0)
                dp[i][j] = min(dp[i][j],dp[i][j-1]+1);
            if(i>0 && j>0)
                dp[i][j] = min(dp[i][j],dp[i-1][j-1]+(p[x][i-1]!=p[y][j-1]));
        }
    return dp[p[x].length()][p[y].length()];
}

int main()
{
    cin >> s >> t >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i+1];
    p[0] = s, p[n+1] = t;
    for(int i = 0; i<n+2; i++)
        for(int j = i+1; j<n+2; j++)
            dist[i][j] = dist[j][i] = edit(i,j);
    for(int i = 0; i<n+2; i++)
        ind[i] = {dist[0][i],i};
    sort(ind,ind+n+2);
    memset(best,-0x3f3f3f3f,sizeof(best));
    best[0] = 0;
    for(int i = 0; i<n+2; i++)
        for(int j = 0; j<i; j++)
            if(dist[0][ind[j].s]+dist[ind[j].s][ind[i].s]==dist[0][ind[i].s] && best[ind[j].s]+1>best[ind[i].s])
                    best[ind[i].s] = max(best[ind[i].s],best[ind[j].s]+1), pv[ind[i].s] = ind[j].s;
    cout << dist[0][n+1] << " " << best[n+1]-1 << endl;
    int cur = pv[n+1];
    while(cur != 0)
        points.push_back(p[cur]), cur = pv[cur];
    for(int i = points.size()-1; i>=0; i--)
        cout << points[i] << endl;
}