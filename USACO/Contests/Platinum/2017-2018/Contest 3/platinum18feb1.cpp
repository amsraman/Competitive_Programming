#include <fstream>
#include <iostream>
#include <algorithm>
#define MAXN (1<<17)
#define INF 2147483647
typedef long long ll;

using namespace std;

int n, m, p0, p1, pt[100000], t[100000];
ll seg[2*MAXN][4], ans[100000];
pair<int,int> y[100000], q1[100000];
pair<pair<int,int>,int> in[100000], q[100000];

ll query(int x, int y, int a)
{
    int low = x+MAXN, high = y+MAXN;
    ll ret = INF;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret,seg[high][a]), high--;
        if(low%2==1) ret = min(ret,seg[low][a]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void update(int k, long long x, int a)
{
    k+=MAXN, seg[k][a] = x;
    while(k>1)
    {
        k/=2;
        seg[k][a] = min(seg[2*k][a],seg[2*k+1][a]);
    }
}

int main()//initialize everything to INF
{
    ifstream infile("slingshot.in");
    ofstream outfile("slingshot.out");
    infile >> n >> m;
    for(int i = 0; i<2*MAXN; i++) seg[i][0] = seg[i][1] = seg[i][2] = seg[i][3] = INF;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first.first >> in[i].first.second >> in[i].second;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> q[i].first.second >> q[i].first.first;
        q[i].second = i;
        q1[i] = make_pair(q[i].first.second,i);
    }
    sort(in,in+n);
    sort(q,q+m);
    sort(q1,q1+m);
    for(int i = 0; i<m; i++)
    {
        while((p0!=n)&&(in[p0].first.first<q1[i].first)) p0++;
        pt[q1[i].second] = p0;
    }
    for(int i = 0; i<n; i++)
    {
        t[i] = in[i].second;
        y[i] = make_pair(in[i].first.second,i);
        update(i,t[i]-in[i].first.first+in[i].first.second,2);
        update(i,t[i]+in[i].first.first+in[i].first.second,3);
    }
    sort(y,y+n);
    for(int i = 0; i<m; i++)
    {
        while((p1!=n)&&(y[p1].first<=q[i].first.first))
        {
            update(y[p1].second,INF,2);
            update(y[p1].second,INF,3);
            update(y[p1].second,t[y[p1].second]-in[y[p1].second].first.first-in[y[p1].second].first.second,0);
            update(y[p1].second,t[y[p1].second]+in[y[p1].second].first.first-in[y[p1].second].first.second,1);
            p1++;
        }
        ans[q[i].second] = max(q[i].first.first,q[i].first.second)-min(q[i].first.first,q[i].first.second);
        ans[q[i].second] = min(ans[q[i].second],query(0,pt[q[i].second]-1,0)+ll(q[i].first.first+q[i].first.second));
        ans[q[i].second] = min(ans[q[i].second],query(pt[q[i].second],n-1,1)+ll(q[i].first.first-q[i].first.second));
        ans[q[i].second] = min(ans[q[i].second],query(0,pt[q[i].second]-1,2)-ll(q[i].first.first-q[i].first.second));
        ans[q[i].second] = min(ans[q[i].second],query(pt[q[i].second],n-1,3)-ll(q[i].first.first+q[i].first.second));
    }
    for(int i = 0; i<m; i++)
    {
        outfile << ans[i] << endl;
    }
}
