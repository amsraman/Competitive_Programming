#include <bits/stdc++.h>

using namespace std;

int t, n, a[200000], diff[200000], ans;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<n-1; i++)
            diff[i] = a[i]-a[i+1];
        int p1 = 0;
        ans = 0;
        while(p1<n-1)
        {
            int p2 = p1;
            while((p2<n-1)&&(diff[p2]==diff[p1]))
                p2++;
            ans = max(ans,p2-p1);
            p1 = p2;
        }
        cout << "Case #" << _ << ": " << ans+1 << endl;
    }
}
