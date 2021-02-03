#include <bits/stdc++.h>

using namespace std;

int t;
long double h, l, w, hp, r;

long double solve_quad(long double b, long double c)
{
    return (-b-sqrt(b*b-4.0*c))/(2.0);
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> h >> l >> w;
        hp = sqrt(h*h+(w/2.0)*(w/2.0));
        r = l*(w/2.0)/(h+hp-w/2.0);
        if(hp>=l+r)
            cout << fixed << setprecision(11) << r << endl;
        else
            cout << fixed << setprecision(11) << solve_quad(-w-2.0*(h-l),(w/2.0)*(w/2.0)+(h-l)*(h-l)) << endl;
    }
}