#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000000
typedef long long ll;

using namespace std;

ll t, cx, cy;
stack<ll> coef;
stack<pair<ll,ll> > lvl;
string s;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> s;
        cx = cy = 0;
        for(int i = 0; i<s.length(); i++)
        {
            if(s[i]=='N')
                cy = (cy+MOD-1)%MOD;
            else if(s[i]=='S')
                cy = (cy+1)%MOD;
            else if(s[i]=='E')
                cx = (cx+1)%MOD;
            else if(s[i]=='W')
                cx = (cx+MOD-1)%MOD;
            else if(isdigit(s[i]))
                coef.push(s[i]-'0'), lvl.push({cx,cy}), cx = cy = 0, i++;
            else if(s[i]=='(')
                coef.push(1), lvl.push({cx,cy}), cx = cy = 0;
            else
                cx = (cx*coef.top()+lvl.top().f)%MOD, cy = (cy*coef.top()+lvl.top().s)%MOD, coef.pop(), lvl.pop();

        }
        cout << "Case #" << cs+1 << ": " << 1+cx << " " << 1+cy << endl;
    }
}
