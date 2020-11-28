#include <bits/stdc++.h>

using namespace std;

int t, n, p, s[100000], sum, ans = INT_MAX;

int main()
{
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        cin >> n >> p;
        for(int i = 0; i<n; i++)
            cin >> s[i];
        sort(s,s+n);
        for(int i = 0; i<n; i++)
        {
            sum+=s[i];
            if(i>p-2)
                ans = min(ans,p*s[i]-sum), sum-=s[i-p+1];
        }
        cout << "Case #" << z+1 << ": " << ans << endl;
        sum = 0, ans = INT_MAX;
    }
}
