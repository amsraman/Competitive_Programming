#include <bits/stdc++.h>

using namespace std;

int t, n, k, a[200000], ans;
bool good[200001];

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n >> k;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<n; i++)
            good[i] = false;
        ans = 0;
        for(int i = n-1; i>=0; i--)
        {
            if((a[i]==1)||(good[i+1]&&(a[i]==a[i+1]+1)))
                good[i] = true;
            if((good[i])&&(a[i]==k))
                ans++;
        }
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
