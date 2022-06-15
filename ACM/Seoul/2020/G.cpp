#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;
typedef long double ld;

using namespace std;

int n;
ll d, pos[1000000];

ld solve(int rev)
{
    ld mn = INF, mx = -INF;
    for(int i = 0; i<n; i++)
    {
        ld cur = pos[i]-(pos[0]+(ll)i*d);
        mn = min(mn,cur), mx = max(mx,cur);
    }
    reverse(pos,pos+n);
    return (mx-mn)/2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> d;
    for(int i = 0; i<n; i++)
        cin >> pos[i];
    cout << fixed << setprecision(1) << min(solve(0),solve(1)) << '\n';
}