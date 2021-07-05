#include <bits/stdc++.h>

using namespace std;

int t, n, str[200000];
string s;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> s;
        str[0] = 1;
        for(int i = 1; i<n; i++)
        {
            if(s[i]>s[i-1])
                str[i] = str[i-1]+1;
            else
                str[i] = 1;
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i<n; i++)
            cout << str[i] << " ";
        cout << endl;
    }
}