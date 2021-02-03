#include <bits/stdc++.h>

using namespace std;

int n = 1e6+1, q, t, a, seg[(1<<21)], lazy[(1<<21)];

void app(int pos, int c)
{
    seg[pos]+=c;
    lazy[pos]+=c;
}

void psh(int pos)
{
    app(2*pos+1,lazy[pos]);
    app(2*pos+2,lazy[pos]);
    lazy[pos] = 0;
}

int qry(int s = 0, int e = n-1, int l = 0)
{
    if(s==e)
        return s;
    int mid = (s+e)/2;
    psh(l);
    if(seg[2*l+2]>=0)
        return qry(mid+1,e,2*l+2);
    else
        return qry(s,mid,2*l+1);
}

void upd(int a, int b, int c, int s = 0, int e = n-1, int l = 0)
{
    if((a==s)&&(b==e))
    {
        app(l,c);
        return;
    }
    int mid = (s+e)/2;
    psh(l);
    if(a<=mid)
        upd(a,min(b,mid),c,s,mid,2*l+1);
    if(b>mid)
        upd(max(a,mid+1),b,c,mid+1,e,2*l+2);
    seg[l] = max(seg[2*l+1],seg[2*l+2]);
}

int main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    cin >> q;
    for(int i = 0; i<=1000000; i++)
        upd(i,i,-i-1);
    while(q--)
    {
        cin >> t >> a;
        if(t==1)
            upd(a,n-1,1);
        if(t==2)
            upd(a,n-1,-1);
        cout << (seg[0]>=0?qry()+1:0) << '\n';
    }
}