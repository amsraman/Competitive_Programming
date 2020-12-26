#include <bits/stdc++.h>
 
using namespace std;
 
int n, dist[11][11];
 
int main()
{
    cin >> n;
    while(n!=0)
    {
        for(int i = 0; i<=n; i++)
            for(int j = 0; j<=n; j++)   
                cin >> dist[i][j];
        for(int k = 0; k<=n; k++)
            for(int i = 0; i<=n; i++)
                for(int j = 0; j<=n; j++)
                    dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
        int tot = 0, ans = 0x3f3f3f3f;
        vector<int> perm;
        for(int i = 1; i<=n; i++)
            perm.push_back(i);
        do
        {
            tot = dist[0][perm[0]]+dist[perm[n-1]][0];
            for(int i = 0; i<n-1; i++)
                tot+=dist[perm[i]][perm[i+1]];
            ans = min(ans,tot);
        } while(next_permutation(perm.begin(),perm.end()));
        cout << ans << endl;
        cin >> n;
    }
}