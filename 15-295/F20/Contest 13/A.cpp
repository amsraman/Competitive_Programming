#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main()
{
    ll b, ans = 0;
    cin >> b;
    for(ll i = 1; i*i<=b; i++)
    {
        if(b%i==0&&i*i!=b)
            ans+=2;
        else if(b%i==0)
            ans++;
    }
    cout << ans << endl;
}