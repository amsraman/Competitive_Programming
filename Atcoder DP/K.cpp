#include <bits/stdc++.h>

using namespace std;

int n, k, a[100];
bool dp[100001];

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<=k; i++)
        for(int j = 0; j<n; j++)
            if(i>=a[j])
                dp[i]|=(!dp[i-a[j]]);
    cout << (dp[k]?"First":"Second") << endl;
}
