#include <bits/stdc++.h>

using namespace std;

int a, b;

int main()
{
    cin >> a >> b;
    int ans = 0;
    while(a!=b)
    {
        if(a>b&&a%2==0)
            a/=2;
        else
            a++;
        ++ans;
    }
    cout << ans << endl;
}