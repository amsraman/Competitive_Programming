#include <bits/stdc++.h>

using namespace std;

int n, val[8] = {-1,1,2,4,7,8,11,13};

int main()
{
    freopen("moobuzz.in","r",stdin);
    freopen("moobuzz.out","w",stdout);
    cin >> n;
    cout << 15*(n/8)+val[n%8] << endl;
}
