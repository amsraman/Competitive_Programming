#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int b, g;
ll fact[20];

ll ncr(int x, int y)
{
    return (fact[x]/(fact[y]*fact[x-y]));
}

int main()
{
    fact[0] = 1;
    for(ll i = 1; i<20; i++)
        fact[i] = i*fact[i-1];
    cin >> b >> g;
    if((b==0)||(g==0))
        cout << 1 << endl;
    else
        cout << (ncr(b+g,g)+(b+g)*(ncr((b+g)/2,b/2)))/(ll(2)*(b+g)) << endl;
}
