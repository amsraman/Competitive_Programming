#include <bits/stdc++.h>
#define A 975889373
#define B 1000000007
typedef long long ll;

using namespace std;

int n, len, pwr[100001], hsh[100001];
string s, t[100000];
char ans[100000];
set<int> lens;
set<pair<int,int>> lib;

int mul(int a, int b)
{
    return ((ll)a*b)%B;
}

int gen(string x)
{
    int ret = 0;
    for(int i = 0; i<x.length(); i++)
        ret = (mul(ret,A)+x[i])%B;
    return ret;
}

int get_hsh(int x, int y)
{
    return (hsh[y+1]-mul(hsh[x],pwr[y-x+1])+B)%B;
}

int main()
{
    freopen("censor.in","r",stdin);
    freopen("censor.out","w",stdout);
    cin >> s >> n;
    for(int i = 0; i<n; i++)
        cin >> t[i];
    for(int i = 0; i<n; i++)
        lib.insert({t[i].length(),gen(t[i])}), lens.insert(t[i].length());
    len = s.length(), pwr[0] = 1;
    for(int i = 1; i<=s.length(); i++)
        pwr[i] = mul(pwr[i-1],A);
    int num = 0;
    for(int i = 0, cur = 0; i<s.length(); i++, cur++)
    {
        hsh[cur+1] = (mul(hsh[cur],A)+s[i])%B, ans[cur] = s[i];
        for(auto x: lens)
            if(lib.count({x,get_hsh(cur-x+1,cur)}))
            {
                len-=x, cur-=x;
                break;
            }
    }
    for(int i = 0; i<len; i++)
        cout << ans[i];
    cout << endl;
}
