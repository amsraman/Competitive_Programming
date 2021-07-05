#include <bits/stdc++.h>

using namespace std;

int t, n, a[300000], ls[300000], rs[300000], ans;

signed main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        ls[0] = rs[n-1] = 1;
        for(int i = 1; i<n; i++)
        {
            if(i==1||a[i]+a[i-2]==2*a[i-1])
                ls[i] = ls[i-1]+1;
            else
                ls[i] = 2;
        }
        for(int i = n-2; i>=0; i--)
        {
            if(i==n-2||a[i]+a[i+2]==2*a[i+1])
                rs[i] = rs[i+1]+1;
            else
                rs[i] = 2;
        }
        ans = min(n,3);
        for(int i = 0; i<n; i++)
        {
            //We either modify a[i] to satisfy a[i+1] OR modify a[i] to satisfy a[i-1]
            //Any additional benefits are bonus and should be taken account of
            if(i<n-2)
            {
                int num = 2*a[i+1]-a[i+2], cur = 1+rs[i+1];
                if(i>1&&a[i-1]-a[i-2]==a[i+2]-a[i+1]&&2*num==a[i-1]+a[i+1])
                    cur+=ls[i-1];
                else if(i>=1&&2*num==(a[i-1]+a[i+1]))
                    ++cur;
                ans = max(ans,cur);
            }
            if(i>1)
            {
                int num = 2*a[i-1]-a[i-2], cur = 1+ls[i-1];
                if(i<n-2&&a[i-1]-a[i-2]==a[i+2]-a[i+1]&&2*num==a[i-1]+a[i+1])
                    cur+=rs[i+1];
                else if(i<=n-2&&2*num==(a[i-1]+a[i+1]))
                    ++cur;
                ans = max(ans,cur);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}