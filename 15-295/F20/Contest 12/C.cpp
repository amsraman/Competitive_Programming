#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n;
ll s, dp[200][200];
pair<ll,ll> p[200];

ll cross(ll a, ll b, ll c, ll d)
{
    return a*d-b*c;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i].f >> p[i].s;
    for(int i = 0; i<n; i++)
        s+=cross(p[i].f,p[i].s,p[(i+1)%n].f,p[(i+1)%n].s);
    if(s<0)
        reverse(p,p+n);
    for(int i = 0; i<n-1; i++)
        dp[i][i+1] = 1;
    for(int i = n-1; i>=0; i--)
        for(int j = i+2; j<n; j++)
            for(int k = i+1; k<j; k++)
                if(cross(p[k].f-p[i].f,p[k].s-p[i].s,p[j].f-p[k].f,p[j].s-p[k].s)>0)
                    dp[i][j] = (dp[i][j]+dp[i][k]*dp[k][j])%MOD;
    cout << dp[0][n-1] << endl;
}