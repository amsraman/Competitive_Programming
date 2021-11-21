#include <bits/stdc++.h>

using namespace std;

int t, n, k, m, b[200000];
bool in[200000];

string solve()
{
    if((n-m)%(k-1)!=0)
        return "NO";
    int under = 0, over = n-m;
    for(int i = 0; i<n; i++)
    {
        if(in[i]&&under>=(k-1)/2&&over>=(k-1)/2)
            return "YES";
        if(!in[i])
            ++under, --over;
    }
    return "NO";
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k >> m;
        for(int i = 0; i<m; i++)
            cin >> b[i];
        for(int i = 0; i<m; i++)
            in[b[i]-1] = true;
        cout << solve() << endl;
        for(int i = 0; i<n; i++)
            in[i] = false;
    }
}