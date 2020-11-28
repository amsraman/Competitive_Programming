#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll l, r, dp[20][2];

string conv(ll x)
{
    string ret = "";
    while(x!=0)
        ret = char('0'+(x%10))+ret, x/=10;
    if(ret.length()==0)
        return "0";
    return ret;
}

ll f(string x)
{
    memset(dp,0,sizeof(dp));
    dp[0][1] = 1;
    for(int i = 0; i<x.length(); i++)
    {
        for(int j = 0; j<(x[i]-'0'); j++)
            if(j%2!=i%2)
                dp[i+1][0]+=(dp[i][0]+dp[i][1]);
        if((x[i]-'0')%2!=i%2)
            dp[i+1][0]+=dp[i][0], dp[i+1][1]+=dp[i][1];
        for(int j = 1+(x[i]-'0'); j<10; j++)
            if(j%2!=i%2)
                dp[i+1][0]+=dp[i][0];
    }
    ll ans = dp[x.length()][0]+dp[x.length()][1], pow = 1;
    for(int i = 0; i<x.length()-1; i++)
        pow*=5, ans+=pow;
    return ans;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> l >> r;
        cout << "Case #" << _ << ": " << f(conv(r))-f(conv(l-1)) << endl;
    }
}
