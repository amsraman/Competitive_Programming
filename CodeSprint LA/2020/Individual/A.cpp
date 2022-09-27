#include <bits/stdc++.h>

using namespace std;

int n, ans;

int main()
{
    cin >> n;
    while(n!=0)
        ans+=(n%2), n/=2;
    cout << ans << endl;
}
