#include <bits/stdc++.h>

using namespace std;

int t, n, k, cur;
string s;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k >> s;
        cur = 0;
        for(int i = 0, j = n-1; i<j; i++, j--)
            cur+=(s[i]!=s[j]);
        cout << "Case #" << _ << ": " << abs(k-cur) << endl;
    }
}