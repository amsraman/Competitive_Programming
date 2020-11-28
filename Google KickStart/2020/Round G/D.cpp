#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

using namespace std;

int t, n, a[5000];
ll pre[5001];
ld bg[5000], ls[5000], dp[5000][5000];

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        memset(bg,0,sizeof(bg));
        memset(ls,0,sizeof(ls));
        for(int i = 0; i<n; i++)
            pre[i+1] = pre[i]+a[i];
        for(int i = n-1; i>=0; i--)
            for(int j = i+1; j<n; j++)
            {
                dp[i][j] = (bg[i]+ls[j])/ld(j-i)+(pre[j+1]-pre[i]);
                bg[i]+=dp[i][j], ls[j]+=dp[i][j];
            }
        cout << "Case #" << cs << ": " << fixed << setprecision(10) << dp[0][n-1] << endl;
    }
}
