#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n, dp[100001];
string s;

int main()
{
    cin >> s;
    n = s.length(), dp[0] = dp[1] = 1;
    for(int i = 1; i<n; i++)
    {
        dp[i+1] = dp[i];
        if((s[i]==s[i-1])&&((s[i]=='u')||(s[i]=='n')))
            dp[i+1] = (dp[i+1]+dp[i-1])%MOD;
    }
    for(int i = 0; i<n; i++)
        if((s[i]=='w')||(s[i]=='m'))
            dp[n] = 0;
    cout << dp[n] << endl;
}