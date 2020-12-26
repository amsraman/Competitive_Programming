#include <bits/stdc++.h>

using namespace std;

int n, m, a[100000], c[100000], c1[100001], ans[100000];

int main()
{
    cin >> n >> m;
    for(int i = 0; i<m; i++)
        cin >> a[i];
    for(int i = 0; i<m; i++)
    {
        c[a[i]-1]++;
        c1[c[a[i]-1]]++;
        if(c1[c[a[i]-1]]==n)
            ans[i] = 1;
    }
    for(int i = 0; i<m; i++)
        cout << ans[i];
    cout << endl;
}