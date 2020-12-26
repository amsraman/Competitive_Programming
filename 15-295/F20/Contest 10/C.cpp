#include <bits/stdc++.h>

using namespace std;

int n, m, ct, num, pf[500000];
string s, t, rem, ans;

int main()
{
    cin >> s >> t;
    n = s.length(), m = t.length();
    for(int i = 1, cur = 0; i<m; i++)
    {
        while(cur>0&&t[i]!=t[cur])
            cur = pf[cur-1];
        if(t[i]==t[cur])
            cur++;
        pf[i] = cur;
    }
    ans = t;
    rem = t.substr(pf[m-1],m-pf[m-1]);
    while(ans.length()<n)
        ans+=rem;
    if(ans.length()>n)
        ans = ans.substr(0,n);
    for(int i = 0; i<n; i++)
        num+=(s[i]-'0'), ct+=(ans[i]-'0');
    for(int i = n-1; i>=0; i--)
    {
        if(ct==num)
            break;
        if(ct<num&&ans[i]=='0')
            ans[i] = '1', ct++;
        else if(ct>num&&ans[i]=='1')
            ans[i] = '0', ct--;
    }
    cout << ans << endl;
}