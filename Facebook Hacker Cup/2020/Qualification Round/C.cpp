#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, n;
ll ans;
pair<ll,ll> tree[800000];
map<ll,ll> m;

int main()
{
    freopen("timber_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> tree[i].f >> tree[i].s;
        sort(tree,tree+n);
        ans = 0;
        for(int i = 0; i<n; i++)
        {
            m[tree[i].f+tree[i].s] = max(m[tree[i].f+tree[i].s],m[tree[i].f]+tree[i].s);
            m[tree[i].f] = max(m[tree[i].f],m[tree[i].f-tree[i].s]+tree[i].s);
            ans = max(ans,max(m[tree[i].f],m[tree[i].f+tree[i].s]));
        }
        for(int i = 0; i<n; i++)
            m[tree[i].f] = m[tree[i].f+tree[i].s] = 0;
        cout << "Case #" << _+1 << ": " << ans << endl;
    }
}
