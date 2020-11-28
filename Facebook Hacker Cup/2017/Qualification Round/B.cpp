#include <bits/stdc++.h>

using namespace std;

int t, n, w[100], l, r, ans;

int main()
{
    freopen("lazy_loading.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
        {
            cin >> w[i];
        }
        sort(w,w+n);
        l = 0, r = n-1, ans = 0;
        while(ceil(50/double(w[r]))<=r-l+1)
        {
            l+=(ceil(50/double(w[r]))-1), r--, ans++;
        }
        cout << "Case #" << z+1 << ": " << ans << endl;
    }
}
