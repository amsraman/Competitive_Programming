#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;
typedef long double ld;

using namespace std;

int n, a[200000];
ll pre[2000001];
pair<int,int> ans;

ld f(int x, int y)
{
    ld med = a[x], mean = (pre[x+1]-pre[x-y]+pre[n]-pre[n-y])/((ld)2*y+1);
    return mean-med;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    sort(a,a+n);
    for(int i = 0; i<n; i++)
        pre[i+1] = pre[i]+a[i];
    for(int i = 0; i<n; i++)
    {
        int lb = 1, ub = min(i,n-i-1);
        while(lb<ub)
        {
            int m1 = lb+(ub-lb)/3, m2 = ub-(ub-lb)/3;
            if(f(i,m1)<f(i,m2))
                lb = m1+1;
            else
                ub = m2-1;
        }
        if(f(i,ub)>f(ans.f,ans.s))
            ans = {i,ub};
    }
    cout << 2*ans.s+1 << endl;
    for(int i = 0; i<=ans.s; i++)
        cout << a[ans.f-ans.s+i] << " ";
    for(int i = 0; i<ans.s; i++)
        cout << a[n-ans.s+i] << " ";
    cout << endl;
}