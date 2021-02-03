#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n, b[50];
ld fact[51], dp[51][51], zer = -0x3f3f3f3f;

ld add(ld x, ld y)
{
    return log(exp(x)+exp(y));
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> b[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<=50; j++)
            dp[i][j] = zer;
    for(int i = 1; i<=50; i++)
        fact[i] = fact[i-1]+log(i);
    for(int i = n-1; i>=0; i--)
        for(int j = b[i]-1; j>=0; j--)
        {
            int ind = i;
            for(int k = i+1; k<n; k++)
                if(b[ind]>=b[k])
                    ind = k;
            if(b[ind]<j)
                continue;
            ld cur = 0;
            for(int k = i; k<n; k++)
            {
                cur+=(log(b[ind]-j)-log(b[k]));
                if(k>=ind)
                    dp[i][j] = add(dp[i][j],cur-fact[k-i+1]+dp[k+1][b[ind]]);
            }
        }
    cout << fixed << setprecision(11) << dp[0][0] << endl;
}