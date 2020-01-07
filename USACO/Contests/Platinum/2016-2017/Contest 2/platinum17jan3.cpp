#include <bits/stdc++.h>

using namespace std;

int n, arr[50], dp[50][50][50][50];
bool v[50][50][50][50];

int solve(int a, int b, int c, int d)
{
    if(a>b)
        return 0;
    if(v[a][b][c][d])
        return dp[a][b][c][d];
    v[a][b][c][d] = true;
    if((a==b)&&(c==d))
    {
        dp[a][b][c][d] = (arr[a]==c);
        return dp[a][b][c][d];
    }
    if(c!=d)
    {
        dp[a][b][c][d] = max(dp[a][b][c][d],solve(a,b,c+1,d));
        dp[a][b][c][d] = max(dp[a][b][c][d],solve(a,b,c,d-1));
    }
    if(a!=b)
    {
        dp[a][b][c][d] = max(dp[a][b][c][d],solve(a+1,b,c,d)+(arr[a]==c));
        dp[a][b][c][d] = max(dp[a][b][c][d],solve(a,b-1,c,d)+(arr[b]==d));
    }
    if(a<b)
        dp[a][b][c][d] = max(dp[a][b][c][d],(arr[b]==c)+(arr[a]==d)+solve(a+1,b-1,c,d));
    return dp[a][b][c][d];
}

int main()
{
    freopen("subrev.in","r",stdin);
    freopen("subrev.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> arr[i];
        arr[i]--;
    }
    cout << solve(0,n-1,0,49) << endl;
}
