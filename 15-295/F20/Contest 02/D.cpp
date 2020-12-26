#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, m;
ll k, p, a[1000][1000], rs[1000], cs[1000], rb[1000001], cb[1000001], pr, pc, ans;
priority_queue<ll> q1, q2;

int main()
{
    cin >> n >> m >> k >> p;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            cin >> a[i][j];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            rs[i]+=a[i][j], cs[j]+=a[i][j];
    for(int i = 0; i<n; i++)
        q1.push(rs[i]);
    for(int i = 0; i<m; i++)
        q2.push(cs[i]);
    for(int i = 1; i<=k; i++)
    {
        ll x = q1.top(), y = q2.top();
        q1.pop(), q2.pop();
        rb[i] = x+rb[i-1], q1.push(x-m*p);
        cb[i] = y+cb[i-1], q2.push(y-n*p);
    }
    ans = rb[0]+cb[k];
    for(ll i = 0; i<=k; i++)
        ans = max(ans,rb[i]+cb[k-i]-i*(k-i)*p);
    cout << ans << endl;
}