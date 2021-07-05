#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, p, q, a[200][200], b[200][200];

int main()
{
    cin >> n >> m;
    for(int i = 0, u; i<n; i++)
    {
        cin >> u;
        b[u-1][i] = 2;
    }
    cin >> p >> q;
    for(int i = 0, u, v; i<p; i++)
    {
        cin >> u >> v;
        a[u-1][v-1] = 3;
    }
    for(int i = 0, u, v; i<q; i++)
    {
        cin >> u >> v;
        b[u-1][v-1] = 1;
        for(int j = 0; j<m; j++)
            if(b[j][v-1]==2)
                a[u-1][j] = max(a[u-1][j],2);
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            for(int k = j+1; k<m; k++)
                if(b[j][i]==1&&b[k][i]==1)
                    a[j][k] = max(a[j][k],1), a[k][j] = max(a[j][j],1);
    for(int i = 0; i<m; i++)
    {
        vector<pair<int,int>> tmp;
        for(int j = 0; j<n; j++)
        {
            int score = 0;
            for(int k = 0; k<m; k++)
                score+=a[i][k]*b[k][j];
            if(b[i][j]>0)
                score = -1;
            tmp.push_back({-score,j+1});
        }
        sort(tmp.begin(),tmp.end());
        cout << tmp[0].s << " " << tmp[1].s << " " << tmp[2].s << endl;
    }
}