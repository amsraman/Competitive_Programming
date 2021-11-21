#include <bits/stdc++.h>

using namespace std;

int n, tb, rl, ans;
char a, b, c, d;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> a >> b >> c >> d;
        tb+=(2-(a-'0')-(b-'0'));
        rl+=(2-(c-'0')-(d-'0'));
    }
    ans = min(tb/2,rl/2);
    tb-=2*ans, rl-=2*ans;
    cout << ans << " " << tb << " " << rl << endl;
}
