#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n;
string s;

bool trypoint(int x, int y)
{
    pair<int,int> cur = {0,0};
    for(int i = 0; i<n; i++)
    {
        if(s[i]=='L'&&(cur.s!=y||cur.f!=x+1))
            cur.f--;
        if(s[i]=='R'&&(cur.s!=y||cur.f!=x-1))
            cur.f++;
        if(s[i]=='U'&&(cur.s!=y-1||cur.f!=x))
            cur.s++;
        if(s[i]=='D'&&(cur.s!=y+1||cur.f!=x))
            cur.s--;
    }
    return (cur.f==0&&cur.s==0);
}

void solve()
{
    pair<int,int> cur = {0,0};
    for(int i = 0; i<n; i++)
    {
        if(s[i]=='L')
            cur.f--;
        if(s[i]=='R')
            cur.f++;
        if(s[i]=='U')
            cur.s++;
        if(s[i]=='D')
            cur.s--;
        if(trypoint(cur.f,cur.s+1)) {
            cout << cur.f << " " << cur.s+1 << endl;
            return;
        } else if(trypoint(cur.f,cur.s-1)) {
            cout << cur.f << " " << cur.s-1 << endl;
            return;
        } else if(trypoint(cur.f-1,cur.s)) {
            cout << cur.f-1 << " " << cur.s << endl;
            return;
        } else if(trypoint(cur.f+1,cur.s)) {
            cout << cur.f+1 << " " << cur.s << endl;
            return;
        }
    }
    cout << 0 << " " << 0 << endl;
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> s;
        s = '!'+s, n = s.length();
        solve();
    }
}