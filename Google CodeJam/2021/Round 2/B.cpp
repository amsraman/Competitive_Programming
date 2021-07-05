#include <bits/stdc++.h>

using namespace std;

int t, n, dp[1000001];
vector<int> factors[1000001];

int main()
{
    for(int i = 2; i<=1e6; i++)
        for(int j = i; j<=1e6; j+=i)
            factors[j].push_back(i);
    dp[0] = 0;
    for(int i = 1; i<=1e6; i++)
        for(int j: factors[i])
            dp[i] = max(dp[i],1+dp[(i/j)-1]);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        int ans = 0;
        for(int i: factors[n])
            if(i>2)
                ans = max(ans,1+dp[(n/i)-1]);
        cout << "Case #" << _ << ": " << ans << endl;
    }
}