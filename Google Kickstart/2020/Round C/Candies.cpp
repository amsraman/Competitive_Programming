#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, q, q1, q2;
ll a[200000], tot, bit1[200010], bit2[200010], ans;
char type;

ll qry(ll k)
{
    ll ret = 0;
    for(int x = k+1; x>0; x-=(x&(-x)))
        ret+=bit1[x-1]*(k+1), ret-=bit2[x-1];
    return ret;
}

void upd(ll l, ll r, ll v)
{
    for(int x = l+1; x<=n; x+=(x&(-x)))
        bit1[x-1]+=v, bit2[x-1]+=l*v;
    for(int x = r+2; x<=n; x+=(x&(-x)))
        bit1[x-1]-=v, bit2[x-1]-=(r+1)*v;
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        ans = tot = 0;
        cin >> n >> q;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<=n; i++)
            bit1[i] = bit2[i] = 0;
        for(int i = n-1; i>=0; i--)
            tot+=(1-2*(i%2))*a[i], upd(i,i,tot);
        tot = qry(n-1);
        while(q--)
        {
            cin >> type >> q1 >> q2;
            if(type=='Q')
            {
                ll temp = (tot-qry(q1-2))-((tot-qry(q2-1))+(q2-q1+1)*(qry(min(n-1,q2))-qry(q2-1)));
                if(q1%2==0)
                    temp = -temp;
                ans+=temp;
            }
            else
            {
                ll temp = q2-a[q1-1];
                if(q1%2==0)
                    temp = -temp;
                upd(0,q1-1,temp), a[q1-1] = q2;
                tot = qry(n-1);
            }
        }
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
