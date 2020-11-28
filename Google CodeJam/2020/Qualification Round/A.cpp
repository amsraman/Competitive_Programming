#include <bits/stdc++.h>

using namespace std;

int t, n, m[100][100], tr, r, c;
bool v[100], rep;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                cin >> m[i][j];
        tr = r = c = 0;
        for(int i = 0; i<n; i++)
            tr+=m[i][i];
        for(int i = 0; i<n; i++)
        {
            rep = false;
            memset(v,false,sizeof(v));
            for(int j = 0; j<n; j++)
                rep|=v[m[i][j]-1], v[m[i][j]-1] = true;
            r+=int(rep);
            rep = false;
            memset(v,false,sizeof(v));
            for(int j = 0; j<n; j++)
                rep|=v[m[j][i]-1], v[m[j][i]-1] = true;
            c+=int(rep);
        }
        cout << "Case #" << cs+1 << ": " << tr << " " << r << " " << c << endl;
    }
}
