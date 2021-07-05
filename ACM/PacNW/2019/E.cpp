#include <bits/stdc++.h>
typedef long long ll;
#define MOD 11092019

using namespace std;

int num[26], ans = 1;
string s;

int mul(int x, int y)
{
    return ((ll)x*y)%MOD;
}

int main()
{
    cin >> s;
    for(int i = 0; i<s.length(); i++)
        ++num[s[i]-'a'];
    for(int i = 0; i<26; i++)
        ans = mul(ans,num[i]+1);
    cout << ans << endl;
}