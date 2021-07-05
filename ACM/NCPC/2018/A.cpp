#include <bits/stdc++.h>

using namespace std;

int n, d, h[100000001], ans;
array<int,3> frogs[100000];

int main()
{
    cin >> n >> d;
    for(int i = 0; i<n; i++)
        cin >> frogs[i][1] >> frogs[i][0] >> frogs[i][2];
    sort(frogs,frogs+n);
    for(int i = n-1; i>=0; i--)
    {
        if(h[frogs[i][0]]+frogs[i][1]>d)
            ++ans;
        for(int j = 0; j<frogs[i][0]; j++)
            if(j+frogs[i][0]<=1e8)
                h[j] = max(h[j],frogs[i][2]+h[j+frogs[i][0]]);
    }
    cout << ans << endl;
}