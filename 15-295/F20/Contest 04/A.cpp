#include <bits/stdc++.h>

using namespace std;

int n, tot, pie[50], dp[50];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> pie[i];
    dp[n-1] = tot = pie[n-1];
    for(int i = n-2; i>=0; i--)
        dp[i] = max(pie[i]+(tot-dp[i+1]),dp[i+1]), tot+=pie[i];
    cout << tot-dp[0] << " " << dp[0] << endl;
}