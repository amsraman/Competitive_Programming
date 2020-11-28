#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, c[1000][1000];
ll ans;

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                cin >> c[i][j];
        ans = 0;
        for(int i = 0; i<n; i++)
        {
            ll tot1 = 0, tot2 = 0;
            for(int j = i; j<n; j++)
                tot1+=c[j-i][j], tot2+=c[j][j-i];
            ans = max(ans,max(tot1,tot2));
        }
        cout << "Case #" << cs << ": " << ans << endl;
    }
}
