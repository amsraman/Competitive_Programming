#include <bits/stdc++.h>

using namespace std;

int n, y, k, ans;
bool v[100];

int main()
{
    cin >> n >> y;
    for(int i = 0; i<y; i++)
    {
        cin >> k;
        if(!v[k])
        {
            v[k] = true;
            ans++;
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(!v[i]) cout << i << endl;
    }
    cout << "Mario got " << ans << " of the dangerous obstacles." << endl;
}
