#include <bits/stdc++.h>

using namespace std;

double a, b, ans = 2e9;

int main()
{
    cin >> a >> b;
    if(int(((a/b)+1)/2)!=0)
        ans = min(ans,(a+b)/(2*(int(a/b+1)/2)));
    if((int(a/b)/2)!=0)
        ans = min(ans,(a+b)/(2*(int(a/b)/2)));
    cout << fixed << setprecision(9) << (ans==2e9?-1:ans) << endl;
}
