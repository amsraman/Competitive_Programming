#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, road1[100000], road2[100000], pos[100000];
vector<int> tree[(1<<18)], bit[(1<<18)];
ll ans;

void bld(int lo = 0, int hi = n-1, int ind = 0)
{
    bit[ind].resize(hi-lo+1);
    if(lo==hi)
    {
        tree[ind].push_back(road2[lo]);
        return;
    }
    int mid = (lo+hi)/2;
    bld(lo,mid,2*ind+1);
    bld(mid+1,hi,2*ind+2);
    for(int pt1 = 0, pt2 = 0; pt1<tree[2*ind+1].size()||pt2<tree[2*ind+2].size();)
    {
        if(pt2==tree[2*ind+2].size()||(pt1!=tree[2*ind+1].size()&&tree[2*ind+1][pt1]<tree[2*ind+2][pt2]))
            tree[ind].push_back(tree[2*ind+1][pt1]), ++pt1;
        else
            tree[ind].push_back(tree[2*ind+2][pt2]), ++pt2;
    }
}

int bit_qry(int ind, int k)
{
    int ret = 0;
    for(k++; k>0; k-=(k&(-k)))
        ret+=bit[ind][k-1];
    return ret;
}

void bit_upd(int ind, int k)
{
    for(k++; k<=bit[ind].size(); k+=(k&(-k)))
        bit[ind][k-1]++;
}

int search(int x, int ind)
{
    int lb = 0, ub = tree[ind].size()-1;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(tree[ind][mid]<=x)
            lb = mid;
        else
            ub = mid-1;
    }
    return (tree[ind][ub]<=x?ub:ub-1);
}

ll qry(int lb, int ub, int lo, int hi, int cur_lo = 0, int cur_hi = n-1, int ind = 0)
{
    if(lo==cur_lo&&hi==cur_hi)
        return (bit_qry(ind,search(ub,ind))-bit_qry(ind,search(lb-1,ind)));
    int mid = (cur_lo+cur_hi)/2;
    if(hi<=mid)
        return qry(lb,ub,lo,hi,cur_lo,mid,2*ind+1);
    if(lo>mid)
        return qry(lb,ub,lo,hi,mid+1,cur_hi,2*ind+2);
    return qry(lb,ub,lo,mid,cur_lo,mid,2*ind+1)+qry(lb,ub,mid+1,hi,mid+1,cur_hi,2*ind+2);
}

void upd(int pos, int lb = 0, int ub = n-1, int ind = 0)
{
    bit_upd(ind,search(road2[pos],ind));
    if(lb==ub)
        return;
    int mid = (lb+ub)/2;
    if(pos<=mid)
        upd(pos,lb,mid,2*ind+1);
    else
        upd(pos,mid+1,ub,2*ind+2);
}

int main()
{
    freopen("friendcross.in","r",stdin);
    freopen("friendcross.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> road1[i];
    for(int i = 0; i<n; i++)
    {
        cin >> road2[i];
        pos[road2[i]-1] = i;
    }
    bld();
    for(int i = 0; i<n; i++)
    {
        ans+=(qry(1,n,pos[road1[i]-1],n-1)-qry(road1[i]-k,road1[i]+k,pos[road1[i]-1],n-1));
        upd(pos[road1[i]-1]);
    }
    cout << ans << endl;
}