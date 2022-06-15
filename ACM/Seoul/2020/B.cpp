#include <bits/stdc++.h>

using namespace std;

int da[6], db[6], ans;

int main()
{
    for(int i = 0; i<6; i++)
        cin >> da[i];
    for(int i = 0; i<6; i++)
        cin >> db[i];
    for(int i = 0; i<6; i++)
        for(int j = 0; j<6; j++)
            if(da[i]>db[j])
                ++ans;
    int k = __gcd(ans,36);
    cout << ans/k << '/' << 36/k << endl;
}