#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a[200000], cmn, ans;

int main()
{
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        cmn = -1, ans = 0;
        for(int i = 0; i<n; i++)
        {
            if((a[i]>cmn)&&((i==n-1)||(a[i]>a[i+1])))
                ans++;
            cmn = max(cmn,a[i]);
        }
        cout << "Case #" << _+1 << ": " << ans << endl;
    }
}
