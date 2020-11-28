#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll a[16][16], score[(1<<16)], dp[(1<<16)];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> a[i][j];
    for(int i = 0; i<(1<<n); i++)
        for(int j = 0; j<n; j++)
            for(int k = j+1; k<n; k++)
                if(((1<<j)&i)&&((1<<k)&i))
                    score[i]+=a[j][k];
    for(int i = 0; i<(1<<n); i++)
        for(int j = i; j>0; j = (j-1)&i)
            dp[i] = max(dp[i],dp[i^j]+score[j]);
    cout << dp[(1<<n)-1] << endl;
}
