#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, x, y, f, sum, ar[3000000], ans;
ll a, b;
bool v[3000000];

int main()
{
    freopen("empty.in","r",stdin);
    freopen("empty.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<k; i++)
    {
        cin >> x >> y >> a >> b;
        for(int j = 1; j<=y; j++)
        {
            f = (a*ll(j)+b)%n;
            ar[f]+=x;
        }
    }
    for(int i = 0; i<n; i++)
    {
        sum+=ar[i];
        if(sum>0) v[i] = true, sum--;
    }
    for(int i = 0; i<n; i++)
    {
        if((sum>0)&&(!v[i])) v[i] = true, sum--;
    }
    for(int i = 0; i<n; i++)
    {
        if(!v[i])
        {
            ans = i;
            break;
        }
    }
    cout << ans << endl;
}
