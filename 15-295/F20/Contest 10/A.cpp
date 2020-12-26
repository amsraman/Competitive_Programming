#include <bits/stdc++.h>

using namespace std;

int n, m, from[26], to[26];
char x, y;
string s;

int main()
{
    cin >> n >> m >> s;
    for(int i = 0; i<26; i++)
        from[i] = i;
    for(int i = 0; i<m; i++)
    {
        cin >> x >> y;
        swap(from[(x-'a')],from[(y-'a')]);
    }
    for(int i = 0; i<26; i++)
        to[from[i]] = i;
    for(int i = 0; i<n; i++)
        cout << char('a'+to[(s[i]-'a')]);
    cout << endl;
}