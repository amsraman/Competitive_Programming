#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, k, a[100000];
pair<int,int> pi[100000];

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        for(int i = 0; i<n; i++)
            pi[i] = {(a[i]+k-1)/k,i};
        sort(pi,pi+n);
        cout << "Case #" << _ << ": ";
        for(int i = 0; i<n; i++)
            cout << pi[i].s+1 << " ";
        cout << endl;

    }
}
