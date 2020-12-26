#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int p, k, ans = 1;
bool vis[1000000];

int mul(int a, int b)
{
    return ((ll)a*b)%MOD;
}

int main()
{
    cin >> p >> k;
    for(int i = 1; i<p; i++)
    {
        int cur = i;
        if(!vis[cur])
            ans = mul(ans,p);
        while(!vis[cur])
            vis[cur] = true, cur = ((ll)cur*k)%p;
    }
    if(k==1)
        ans = mul(ans,p);
    cout << ans << endl;
}