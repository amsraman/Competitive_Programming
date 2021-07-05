#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007

using namespace std;

int t, n, k, ans;
string s, pl;

int mul(int a, int b)
{
    return ((ll)a*b)%MOD;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k >> s;
        ans = 0, pl = "";
        for(int i = 0; i<(n+1)/2; i++)
            ans = (mul(ans,k)+s[i]-'a')%MOD, pl+=s[i];
        for(int i = n/2-1; i>=0; i--)
            pl+=s[i];
        if(pl<s)
            ans = (ans+1)%MOD;
        cout << "Case #" << _ << ": " << ans << endl;
    }
}