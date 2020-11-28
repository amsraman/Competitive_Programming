#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int r, c, k, clr[750][750], dp[750][750];
vector<int> cols[562501], bit[562501];

int qry(int ind, int x)
{
    int ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret = (ret+bit[ind][x-1])%MOD;
    return ret;
}

void upd(int ind, int x, int k)
{
    for(x++; x<=bit[ind].size(); x+=(x&(-x)))
        bit[ind][x-1] = (bit[ind][x-1]+k)%MOD;
}

int main()
{
    freopen("hopscotch.in","r",stdin);
    freopen("hopscotch.out","w",stdout);
    cin >> r >> c >> k;
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            cin >> clr[i][j];
    for(int j = 0; j<c; j++)
        for(int i = 0; i<r; i++)
            if(cols[clr[i][j]].empty()||cols[clr[i][j]].back()!=j)
                cols[clr[i][j]].push_back(j), bit[clr[i][j]].push_back(0);
    for(int i = 0; i<c; i++)
        cols[0].push_back(i), bit[0].push_back(0);
    upd(0,0,1), upd(clr[0][0],0,1);
    for(int i = 1; i<r; i++)
        for(int j = c-1; j>=0; j--)
        {
            int lb = 0, ind = cols[clr[i][j]].size()-1;
            while(lb<ind)
            {
                int mid = (lb+ind)/2;
                if(cols[clr[i][j]][mid]<j)
                    lb = mid+1;
                else
                    ind = mid;
            }
            dp[i][j] = (qry(0,j-1)-qry(clr[i][j],ind-1)+MOD)%MOD;
            upd(clr[i][j],ind,dp[i][j]);
            upd(0,j,dp[i][j]);
        }
    cout << dp[r-1][c-1] << endl;
}
