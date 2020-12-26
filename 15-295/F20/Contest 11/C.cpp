#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

int n, a[100000];
ll seg[(1<<19)], ans;

ll qmin(int low, int high)
{
    low+=(1<<18), high+=(1<<18);
    ll ret = INF;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret,seg[high]), high--;
        if(low%2==1) ret = min(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void update(int k, ll x)
{
    k+=(1<<18), seg[k] = x;
    while(k>1)
    {
        k/=2;
        seg[k] = min(seg[2*k],seg[2*k+1]);
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i<n-1; i++)
        cin >> a[i];
    for(int i = 0; i<(1<<19); i++)
        seg[i] = INF;
    update(n-1,n-1);
    for(int i = n-2; i>=0; i--)
    {
        ll temp = qmin(i+1,a[i]-1)-i+(n-a[i]);
        update(i,temp+i);
        ans+=temp;
    }
    cout << ans << endl;
}
