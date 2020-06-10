#include <bits/stdc++.h>

using namespace std;

int t, u, co[26], zer;
long long m;
string d[10000];
pair<int,int> hi[26];
bool vis[26];

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        for(int i = 0; i<26; i++)
            co[i] = 0, vis[i] = false;
        cin >> u;
        for(int i = 0; i<10000; i++)
            cin >> m >> d[i];
        for(int i = 0; i<10000; i++)
            co[(d[i][0]-'A')]++;
        for(int i = 0; i<10000; i++)
            for(int j = 0; j<d[i].length(); j++)
                vis[(d[i][j]-'A')] = true;
        for(int i = 0; i<26; i++)
            hi[i] = {co[i],i};
        sort(hi,hi+26);
        reverse(hi,hi+26);
        cout << "Case #" << cs+1 << ": ";
        zer = -1;
        for(int i = 0; i<26; i++)
            if((co[i]==0)&&(vis[i]))
                zer = i;
        if(zer==-1)
            cout << char('A'+hi[25].second);
        else
            cout << char('A'+zer);
        for(int i = 0; i<9; i++)
            cout << char('A'+hi[i].second);
        cout << endl;
    }
}
