#include <bits/stdc++.h>

using namespace std;

double prob[6], ev, cur, ans = 10;

int main()
{
    for(int i = 0; i<6; i++)
        cin >> prob[i];
    for(int i = 1; i<=6; i++)
        ev+=(prob[i-1]*i);
    for(int i = 0; i<6; i++)
    {
        cur = ((ev-3.5)/prob[i]);
        if(abs(ev-prob[i]*double(i+1)+prob[i]*double(i+1-cur)-3.5)<0.1)
            if(abs(cur)<abs(ans))
                ans = abs(cur);
    }
    cout << fixed << setprecision(3) << ans << endl;
}