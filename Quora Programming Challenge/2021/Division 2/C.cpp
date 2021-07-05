#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, pos[500000], num[500000][2], ans;
ll bit[500000][4], cost[500000];
pair<ll,ll> p[500000];
pair<pair<int,int>,int> ord[500000], rev_ord[500000];

void upd(int k, ll x, int ind)
{
    for(k++; k<=n; k+=(k&(-k)))
        bit[k-1][ind]+=x;
}

void num_upd(int k, int x, int ind)
{
    for(k++; k<=n; k+=(k&(-k)))
        num[k-1][ind]+=x;
}

ll qry(int k, int ind)
{
    ll ret = 0;
    for(k++; k>0; k-=(k&(-k)))
        ret+=bit[k-1][ind];
    return ret;
}

int num_qry(int k, int ind)
{
    int ret = 0;
    for(k++; k>0; k-=(k&(-k)))
        ret+=num[k-1][ind];
    return ret;
}

ll range_sum(int x, int y, int ind)
{
    return qry(y,ind)-qry(x-1,ind);
}

ll get_num(int x, int y, int ind)
{
    return num_qry(y,ind)-num_qry(x-1,ind);
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i].f >> p[i].s;
    for(int i = 0; i<n; i++)
        ord[i] = {{p[i].f-p[i].s,p[i].s+p[i].f},i}, rev_ord[i] = {{p[i].s+p[i].f,p[i].f-p[i].s},i};
    sort(ord,ord+n), sort(rev_ord,rev_ord+n);
    for(int i = 0; i<n; i++)
        pos[rev_ord[i].s] = i;
    for(int i = 0; i<n; i++)
        upd(pos[i],p[i].f,2), upd(pos[i],p[i].s,3), num_upd(pos[i],1,1);
    for(int i = 0; i<n; i++)
    {
        ll num_x = get_num(0,pos[ord[i].s],0)-get_num(pos[ord[i].s]+1,n-1,1), num_y = -get_num(pos[ord[i].s]+1,n-1,0)+get_num(0,pos[ord[i].s],1);
        cost[ord[i].s] = p[ord[i].s].f*num_x+p[ord[i].s].s*num_y-range_sum(0,pos[ord[i].s],0)+range_sum(pos[ord[i].s]+1,n-1,1)+range_sum(pos[ord[i].s]+1,n-1,2)-range_sum(0,pos[ord[i].s],3);
        upd(pos[ord[i].s],p[ord[i].s].f,0), upd(pos[ord[i].s],p[ord[i].s].s,1);
        upd(pos[ord[i].s],-p[ord[i].s].f,2), upd(pos[ord[i].s],-p[ord[i].s].s,3);
        num_upd(pos[ord[i].s],-1,1), num_upd(pos[ord[i].s],1,0);
    }
    for(int i = 0; i<n; i++)
        if(cost[i]<cost[ans])
            ans = i;
    cout << ans+1 << endl;
}