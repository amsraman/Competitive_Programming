#include <bits/stdc++.h>

using namespace std;

int t, x, y, ans;
string m;
bool found;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> x >> y >> m;
        found = false;
        for(ans = 0; ans<m.length(); ans++)
        {
            if(m[ans]=='N') y++;
            if(m[ans]=='S') y--;
            if(m[ans]=='E') x++;
            if(m[ans]=='W') x--;
            if((abs(x)+abs(y))<=(ans+1))
                found = true;
            if(found)
                break;
        }
        cout << "Case #" << cs+1 << ": ";
        if(found)
            cout << ans+1 << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
}
