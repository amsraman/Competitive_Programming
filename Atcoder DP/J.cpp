#include <bits/stdc++.h>

using namespace std;

int n, a[300], ind[3];
double dp[301][301][301];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<n; i++)
        ind[3-a[i]]++;
    ind[1]+=ind[0], ind[2]+=ind[1];
    for(int i = 0; i<=ind[0]; i++)
        for(int j = i; j<=ind[1]; j++)
            for(int k = j; k<=ind[2]; k++)
            {
                if(i>0)
                    dp[i][j][k]+=double(i)/double(n)*(1+dp[i-1][j][k]);
                if(j>i)
                    dp[i][j][k]+=double(j-i)/double(n)*(1+dp[i][j-1][k]);
                if(k>j)
                    dp[i][j][k]+=double(k-j)/double(n)*(1+dp[i][j][k-1]);
                if(k>0)
                    dp[i][j][k]+=double(n-k)/double(n), dp[i][j][k]*=double(n)/double(k);
            }
    cout << fixed << setprecision(10) << dp[ind[0]][ind[1]][ind[2]] << endl;
}
