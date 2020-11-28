#include <bits/stdc++.h>

using namespace std;

int t, n;
double p, dp[8000][8000];

int main()
{
    freopen("elimination_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> p;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                dp[i][j] = 0;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                double a = i, b = j, c = (a+b+1)*(a+b);
                if(i>0)
                    dp[i][j]+=dp[i-1][j]*(a*(a-1)/c+2*a*p/c+2*a*b*p/c);
                if(j>0)
                    dp[i][j]+=dp[i][j-1]*(b*(b-1)/c+2*b*(1-p)/c+2*a*b*(1-p)/c);
                dp[i][j]+=1;
                if(i+j<=1)
                    dp[i][j] = 1;
            }
        cout << "Case #" << _ << ": " << endl;
        for(int i = 0; i<n; i++)
            cout << fixed << setprecision(9) << dp[i][n-i-1] << endl;
    }
}
