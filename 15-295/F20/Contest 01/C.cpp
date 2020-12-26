#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
ll n, sum, hs;
 
int main()
{
    cin >> n;
    sum = n*(n-1)/2, hs = ll(sqrt(sum))+1;
    if(hs*(hs-1)>sum)
        hs--;
    if(n==2)
        cout << 1 << endl;
    else if(n==5)
        cout << 2 << endl;
    else
        cout << n-hs << endl;
}