#include <bits/stdc++.h>

using namespace std;

int n, a[100000], cur, ans;

int main()
{
    freopen("shadow.in","r",stdin);
    freopen("shadow.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    cur = a[0]+a[1]+a[2]+a[3]+a[4];
    ans = cur;
    for(int i = 5; i<n; i++)
        cur+=a[i], cur-=a[i-5], ans = max(ans,cur);
    cout << ans << endl;
}
