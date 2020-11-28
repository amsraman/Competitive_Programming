#include <bits/stdc++.h>

using namespace std;

int t, h, s, x, y, z, st;
double dp[20001][21], ans;
bool v[20001][21];
string sp;

double prob(int a, int b)
{
    if(a<=0) return 1;
    else if(b==0) return 0;
    if(v[a][b]) return dp[a][b];
    dp[a][b] = 0;
    for(int i = 0; i<y; i++) dp[a][b]+=prob(a-i-1,b-1);
    dp[a][b]/=double(y), v[a][b] = true;
    return dp[a][b];
}

int main()
{
    freopen("fighting_the_zombie.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cout << fixed << setprecision(6);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> h >> s;
        ans = 0;
        for(int i = 0; i<s; i++)
        {
            cin >> sp;
            memset(v,false,sizeof(v)), x = y = z = 0;
            if(sp[1]=='d') x = (sp[0]-'0'), st = 1;
            else x = 10*(sp[0]-'0')+(sp[1]-'0'), st = 2;
            if((st+2==sp.length())||(sp[st+2]=='+')||(sp[st+2]=='-')) y = (sp[st+1]-'0');
            else y = 10*(sp[st+1]-'0')+(sp[st+2]-'0');
            if(sp.find('+')!=string::npos) st = sp.find('+')+1, z = atoi(sp.substr(st,sp.length()-st).c_str());
            if(sp.find('-')!=string::npos) st = sp.find('-')+1, z = -atoi(sp.substr(st,sp.length()-st).c_str());
            ans = max(ans,prob(h-z,x));
        }
        cout << "Case #" << _+1 << ": " << ans << endl;
    }
}
