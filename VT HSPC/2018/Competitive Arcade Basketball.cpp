#include <bits/stdc++.h>

using namespace std;

int n, p, m, points, wc;
string names[100000], cur;
map<string,int> ms;

int main()
{
    cin >> n >> p >> m;
    for(int i = 0; i<n; i++)
    {
        cin >> names[i];
    }
    for(int i = 0; i<m; i++)
    {
        cin >> cur >> points;
        ms[cur]+=points;
    }
    for(int i = 0; i<n; i++)
    {
        if(ms[names[i]]>=p)
        {
            wc++;
            cout << names[i] << " wins!" << endl;
        }
    }
    if(wc==0) cout << "No winner!" << endl;
}
