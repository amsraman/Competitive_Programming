#include <bits/stdc++.h>

using namespace std;

int t, n, q, path[26][26];
string names[50000];

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> q;
        for(int i = 0; i<n; i++)
            cin >> names[i];
        memset(path,0,sizeof(path));
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<names[i].length(); j++)
                for(int k = j+1; k<names[i].length(); k++)
                    path[(names[i][j]-'A')][(names[i][k]-'A')]|=1, path[(names[i][k]-'A')][(names[i][j]-'A')] = path[(names[i][j]-'A')][(names[i][k]-'A')];
        }
        for(int i = 0; i<26; i++)
            for(int j = 0; j<26; j++)
                if(path[i][j]==0)
                    path[i][j] = 0x3f3f3f3f;
        for(int i = 0; i<26; i++)
            path[i][i] = 0;
        //floyd-warshall
        for(int k = 0; k<26; k++)
            for(int i = 0; i<26; i++)
                for(int j = 0; j<26; j++)
                    path[i][j] = min(path[i][j],path[i][k]+path[k][j]);
        cout << "Case #" << _ << ": ";
        for(int i = 0, x, y; i<q; i++)
        {
            cin >> x >> y;
            int ans = 0x3f3f3f3f;
            for(int j = 0; j<names[x-1].length(); j++)
                for(int k = 0; k<names[y-1].length(); k++) {
                    ans = min(ans,path[(names[x-1][j]-'A')][(names[y-1][k]-'A')]);
                }
            cout << (ans>1e6?-1:ans+2) << " ";
        }
        cout << endl;
    }
}
