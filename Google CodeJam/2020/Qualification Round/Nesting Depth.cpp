#include <bits/stdc++.h>

using namespace std;

int t, cur;
string s, ans;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> s;
        cur = 0, ans = "";
        for(int i = 0; i<s.length(); i++)
        {
            for(int j = 0; j<abs((s[i]-'0')-cur); j++)
                ans+=char(40+(cur>(s[i]-'0')));
            ans+=s[i];
            cur = (s[i]-'0');
        }
        for(int i = 0; i<(s[s.length()-1]-'0'); i++)
            ans+=')';
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
