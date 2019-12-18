#include <bits/stdc++.h>
#define MAXN (1<<16)
#define INF 0xffffffffff
typedef long long ll;

using namespace std;

int n, d, m, a, b;
ll seg[2*MAXN][4], ans;

ll query(int low, int high)
{
    low+=MAXN, high+=MAXN;
    ll r11 = -INF, r12 = 0, r13 = -INF, r14 = -INF, r21, r22, r23, r24;
    while(low<=high)
    {
        if(high%2==0)
        {
            r21 = max(max(seg[high][0]+r11,seg[high][0]+r13),seg[high][1]+r13);
            r22 = max(max(seg[high][0]+r12,seg[high][0]+r14),seg[high][1]+r14);
            r23 = max(max(seg[high][2]+r11,seg[high][2]+r13),seg[high][3]+r13);
            r24 = max(max(seg[high][2]+r12,seg[high][2]+r14),seg[high][3]+r14);
            if(r13==-INF) r11 = seg[high][0], r12 = seg[high][1], r13 = seg[high][2], r14 = seg[high][3];
            else r11 = r21, r12 = r22, r13 = r23, r14 = r24;
            high--;
        }
        if(low%2==1)
        {
            r21 = max(max(r11+seg[low][0],r11+seg[low][2]),r12+seg[low][2]);
            r22 = max(max(r11+seg[low][1],r11+seg[low][3]),r12+seg[low][3]);
            r23 = max(max(r13+seg[low][0],r13+seg[low][2]),r14+seg[low][2]);
            r24 = max(max(r13+seg[low][1],r13+seg[low][3]),r14+seg[low][3]);
            if(r13==-INF) r11 = seg[low][0], r12 = seg[low][1], r13 = seg[low][2], r14 = seg[low][3];
            else r11 = r21, r12 = r22, r13 = r23, r14 = r24;
            low++;
        }
        low/=2, high/=2;
    }
    return max(max(r11,r12),max(r13,r14));
}

void update(int k, ll x)
{
    k+=MAXN, seg[k][1] = x;
    while(k>1)
    {
        k/=2;
        seg[k][0] = max(max(seg[2*k][0]+seg[2*k+1][0],seg[2*k][0]+seg[2*k+1][2]),seg[2*k][1]+seg[2*k+1][2]);
        seg[k][1] = max(max(seg[2*k][0]+seg[2*k+1][1],seg[2*k][0]+seg[2*k+1][3]),seg[2*k][1]+seg[2*k+1][3]);
        seg[k][2] = max(max(seg[2*k][2]+seg[2*k+1][0],seg[2*k][2]+seg[2*k+1][2]),seg[2*k][3]+seg[2*k+1][2]);
        seg[k][3] = max(max(seg[2*k][2]+seg[2*k+1][1],seg[2*k][2]+seg[2*k+1][3]),seg[2*k][3]+seg[2*k+1][3]);
    }
}

int main()
{
    freopen("optmilk.in","r",stdin);
    freopen("optmilk.out","w",stdout);
    for(int i = 0; i<2*MAXN; i++) seg[i][0] = seg[i][1] = seg[i][3] = -INF;
    cin >> n >> d;
    for(int i = 0; i<n; i++)
    {
        cin >> m;
        update(i,m);
    }
    for(int i = 0; i<d; i++)
    {
        cin >> a >> b;
        update(a-1,b);
        ans+=query(0,n-1);
    }
    cout << ans << endl;
}
