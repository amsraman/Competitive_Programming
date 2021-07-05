#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, q, seg[(1<<18)], lazy[(1<<18)];

void app(int pos, int c)
{
    seg[pos] = c;
    lazy[pos] = c;
}
 
void psh(int pos)
{
    app(2*pos+1,lazy[pos]);
    app(2*pos+2,lazy[pos]);
    lazy[pos] = 0;
}
 
int qry(int a, int b, int s = 0, int e = n+1, int l = 0)
{
    if((a==s)&&(b==e))
        return seg[l];
    int mid = (s+e)/2;
    if(lazy[l]!=0)
        psh(l);
    if(b<=mid)
        return qry(a,b,s,mid,2*l+1);
    if(a>mid)
        return qry(a,b,mid+1,e,2*l+2);
    return max(qry(a,mid,s,mid,2*l+1),qry(mid+1,b,mid+1,e,2*l+2));
}
 
void upd(int a, int b, int c, int s = 0, int e = n+1, int l = 0)
{
    if((a==s)&&(b==e))
    {
        app(l,c);
        return;
    }
    int mid = (s+e)/2;
    if(lazy[l]!=0)
        psh(l);
    if(a<=mid)
        upd(a,min(b,mid),c,s,mid,2*l+1);
    if(b>mid)
        upd(max(a,mid+1),b,c,mid+1,e,2*l+2);
    seg[l] = max(seg[2*l+1],seg[2*l+2]);
}

int main()
{
    cin >> n >> q;
    for(int i = 0, h; i<n; i++)
    {
        cin >> h;
        upd(i+1,i+1,h);
    }
    upd(0,0,INF), upd(n+1,n+1,INF);
    for(int i = 0, type, a, b, x; i<q; i++)
    {
        cin >> type;
        if(type==1)
        {
            cin >> x;
            int lb1 = 0, ub1 = x, lb2 = x, ub2 = n+1, targ = qry(x,x);
            while(lb1<ub1)
            {
                int mid = (lb1+ub1+1)/2;
                if(qry(mid,x)>targ)
                    lb1 = mid;
                else
                    ub1 = mid-1;
            }
            while(lb2<ub2)
            {
                int mid = (lb2+ub2)/2;
                if(qry(x,mid)>targ)
                    ub2 = mid;
                else
                    lb2 = mid+1;
            }
            cout << ub2-ub1-1 << endl;
        }
        if(type==2)
        {
            cin >> a >> x;
            upd(a,a,x);
        }
        if(type==3)
        {
            cin >> a >> b >> x;
            upd(a,b,x);
        }
    }
}