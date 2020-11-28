#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll m, dp[10001][1230];
vector<ll> primes;

bool isPrime(ll x)
{
    for(ll i = 2; i*i<=x; i++)
        if((x%i)==0)
            return false;
    return true;
}

int main()
{
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    cin >> n >> m;
    for(int i = 2; i<=n; i++)
        if(isPrime(i))
            primes.push_back(i);
    for(int i = 0; i<=primes.size(); i++)
        dp[0][i] = 1;
    for(int i = 1; i<=n; i++)
    {
        dp[i][0] = dp[i-1][0];
        for(int j = 1; j<=primes.size(); j++)
        {
            dp[i][j] = dp[i][j-1];
            ll cur = primes[j-1];
            while(cur<=i)
            {
                dp[i][j] = (dp[i][j]+cur*dp[i-cur][j-1])%m;
                cur*=primes[j-1];
            }
        }
    }
    cout << dp[n][primes.size()] << endl;
}
