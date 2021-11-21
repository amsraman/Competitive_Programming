#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, m, q, num;
multiset<pair<int,int>> ms, ps;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> q;
    while(q--)
    {
        cin >> t;
        if(t==1)
        {
            cin >> m;
            ms.insert({++num,-m});
            ps.insert({-m,num});
        }
        else if(t==2)
        {
            pair<int,int> tmp = *(ms.begin());
            ms.erase(ms.begin());
            ps.erase(ps.find({tmp.s,tmp.f}));
            cout << tmp.f << " ";
        }
        else
        {
            pair<int,int> tmp = *(ps.begin());
            ps.erase(ps.begin());
            ms.erase(ms.find({tmp.s,tmp.f}));
            cout << tmp.s << " ";
        }
    }
}