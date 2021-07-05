#include <bits/stdc++.h>

using namespace std;

int t, n, l[100], ans;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> l[i];
        ans = 0;
        for(int i = 0; i<n-1; i++)
        {
            int mn = i;
            for(int j = i+1; j<n; j++)
                if(l[j]<l[mn])
                    mn = j;
            ans+=(mn-i+1);
            for(int p1 = i, p2 = mn; p1<p2; p1++, p2--)
                swap(l[p1],l[p2]);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}