#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a;
map<int,ll> cnt;
ll ans;
string s;

int main()
{
    cin >> a >> s;
    n = s.length();
    for(int i = 0, cur = 0; i<n; i++, cur = 0)
    {
        for(int j = i; j<s.length(); j++)
            cur+=(s[j]-'0'), ++cnt[cur];
    }
    for(int i = 1; i*i<=a; i++)
        if(a%i==0)
        {
            ans+=cnt[i]*cnt[a/i];
            if(i!=a/i)
                ans+=cnt[i]*cnt[a/i];
        }
    if(a==0)
        ans = ((ll)n*n*(n+1)*(n+1)/4-((ll)n*(n+1)/2-cnt[0])*((ll)n*(n+1)/2-cnt[0]));
    cout << ans << endl;
}