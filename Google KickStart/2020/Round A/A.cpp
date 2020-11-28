#include <bits/stdc++.h>

using namespace std;

int t, n, a[100000], b, ans;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n >> b;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        sort(a,a+n);
        while((b-a[ans]>=0)&&(ans<n))
            b-=a[ans], ans++;
        cout << "Case #" << cs+1 << ": " << ans << endl;
        ans = 0;
    }
}
