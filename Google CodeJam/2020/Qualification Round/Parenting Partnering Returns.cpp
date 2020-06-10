#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n;
pair<pair<int,int>,int> act[1000];
pair<int,int> c1, c2;
string ans;
bool ok;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        ok = true, ans = "";
        cin >> n;
        for(int i = 0; i<n; i++)
        {
            cin >> act[i].f.f >> act[i].f.s;
            act[i].s = i;
            ans+="C";
        }
        sort(act,act+n);
        for(int i = 1; i<n; i++)
        {
            if(act[i].f.f>=act[i-1].f.s)
                ans[act[i].s] = ans[act[i-1].s];
            else
                ans[act[i].s] = (ans[act[i-1].s]^'C'^'J');
        }
        c1 = c2 = {-1,-1};
        for(int i = 0; i<n; i++)
        {
            if(((ans[act[i].s]=='C')&&(act[i].f.f<c1.s))||((ans[act[i].s]=='J')&&(act[i].f.f<c2.s)))
                ok = false;
            if(ans[act[i].s]=='C')
                c1 = act[i].f;
            else
                c2 = act[i].f;
        }
        cout << "Case #" << cs+1 << ": " << (ok?(ans):("IMPOSSIBLE")) << endl;
    }
}
