#include <bits/stdc++.h>

using namespace std;

int n, m, dp[500][500][7];
bool clr[500][500];
string s, chars = "BCGKMRY";
map<char,int> ind;

int main()
{
    cin >> s >> m;
    n = s.length();
    for(int i = 0; i<7; i++)
        ind[chars[i]] = i;
    memset(dp,-0x3f3f3f3f,sizeof(dp));
    for(int i = 0; i<n; i++)
        dp[i][i][ind[s[i]]] = 1;
    for(int i = n-1; i>=0; i--)
        for(int j = i+1; j<n; j++)
            for(int id = 0; id<7; id++) {
                for(int k = i; k<j; k++)
                {
                    int cur = max(dp[i][k][id],(!clr[i][k])*dp[i][k][id])+max(dp[k+1][j][id],(!clr[k+1][j])*dp[k+1][j][id]);
                    dp[i][j][id] = max(dp[i][j][id],cur);
                    if(dp[i][j][id]>=m)
                        clr[i][j] = true;
                }
            }
    if(m<=1)
        clr[0][n-1] = true;
    cout << (clr[0][n-1]?"Yes":"No") << endl;
}