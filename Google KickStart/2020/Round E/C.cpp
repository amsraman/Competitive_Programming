#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, n, ans;
ll tot, bit[100000], cur;
pair<ll,ll> toy[100000];
set<int> ind;
set<pair<ll,ll>> ts;
bool early;

ll qry(int x)
{
    ll ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret+=bit[x-1];
    return ret;
}

void upd(int k, ll x)
{
    for(k++; k<=n; k+=(k&(-k)))
        bit[k-1]+=x;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> toy[i].f >> toy[i].s;
        tot = cur = 0, early = false;
        for(int i = 0; i<n; i++)
            tot+=toy[i].f, ts.insert({toy[i].f+toy[i].s,i}), upd(i,toy[i].f);
        for(int i = 0; i<n; i++)
        {
            while((!ts.empty())&&(--ts.end())->f>tot) {
                ind.insert((--ts.end())->s), ts.erase(--ts.end());
            }
            if(ind.empty())
            {
                ans = i, early = true;
                break;
            }
            int ix = *(ind.begin());
            if(qry(n-1)+qry(ix-1)>cur)
                cur = qry(n-1)+qry(ix-1), ans = i;
            ind.erase(ind.begin());
            upd(ix,-toy[ix].f);
            tot-=toy[ix].f;
        }
        cout << "Case #" << _ << ": ";
        if(early)
            cout << ans << " INDEFINITELY" << endl;
        else
            cout << ans << " " << cur << endl;
        ts.clear(), ind.clear();
        for(int i = 0; i<n; i++)
            bit[i] = 0;
    }
}
