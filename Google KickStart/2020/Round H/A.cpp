#include <bits/stdc++.h>

using namespace std;

int t, n, k, s;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k >> s;
        cout << "Case #" << _ << ": " << n-s+k+min(s,k-s) << endl;
    }
}
