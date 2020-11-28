#include <bits/stdc++.h>
#define MOD 1000000007
#define f first
#define s second
typedef long long ll;

using namespace std;

int n;
ll pow2[100001], diff[200001], ans;
pair<int,int> seg[100000];

int main()
{
    freopen("help.in","r",stdin);
    freopen("help.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> seg[i].f >> seg[i].s;
    pow2[0] = 1;
    for(int i = 1; i<=n; i++)
        pow2[i] = (pow2[i-1]*2)%MOD;
    for(int i = 0; i<n; i++)
        diff[seg[i].f]++, diff[seg[i].s]--;
    for(int i = 1; i<=2*n; i++)
        diff[i]+=diff[i-1];
    for(int i = 1; i<=2*n; i++)
        if(diff[i]==diff[i-1]+1)
            ans = (ans+pow2[n-diff[i-1]-1])%MOD;
    cout << ans << endl;
}
