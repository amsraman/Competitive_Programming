#include<bits/stdc++.h>

using namespace std;

int t, n, h[100], ans;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> h[i];
        for(int i = 1; i<n-1; i++)
            if((h[i]>h[i-1])&&(h[i]>h[i+1]))
                ans++;
        cout << "Case #" << cs+1 << ": " << ans << endl;
        ans = 0;
    }
}
