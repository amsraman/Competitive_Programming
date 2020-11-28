#include <bits/stdc++.h>

using namespace std;

int a, b;

int main()
{
    freopen("relprimes.in","r",stdin);
    freopen("relprimes.out","w",stdout);
    cin >> a >> b;
    cout << (__gcd(a,b)==1) << endl;
}
