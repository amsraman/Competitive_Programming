#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, q, a, b, arr[5000];
ll counts[2000001], dp[5000][5000];

int main()
{
    freopen("threesum.in","r",stdin);
    freopen("threesum.out","w",stdout);
    cin >> n >> q;
    for(int i = 0; i<n; i++)
        cin >> arr[i];
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(abs(arr[i]+arr[j])<=1000000)
                dp[i][j]+=counts[1000000-arr[i]-arr[j]];
            counts[arr[j]+1000000]++;
        }
        for(int j = i+1; j<n; j++)
            counts[arr[j]+1000000] = 0;
    }
    for(int i = n-1; i>=0; i--)
        for(int j = i+2; j<n; j++)
            dp[i][j]+=(dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]);
    for(int i = 0; i<q; i++)
    {
        cin >> a >> b;
        cout << dp[a-1][b-1] << endl;
    }
}
