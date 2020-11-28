#include <bits/stdc++.h>

using namespace std;

int n, m, p[100], t[1000], tc;
bool taken[1000];

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++) cin >> p[i];
    for(int i = 0; i<m; i++) cin >> t[i];
    for(int i = 0; i<n; i++)
    {
        int dist = 0x3f3f3f3f, opt;
        for(int j = 0; j<m; j++)
        {
            if(abs(p[i]-t[j])<dist) opt = j, dist = abs(p[i]-t[j]);
        }
        taken[opt] = true;
    }
    for(int i = 0; i<m; i++)
    {
        if(taken[i]) tc++;
    }
    cout << n-tc << endl;
}
