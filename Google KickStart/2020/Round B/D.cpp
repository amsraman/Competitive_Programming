#include <bits/stdc++.h>

using namespace std;

int t, w, h, l, u, r, d;
double fact[200001], ans;

double ncr(int a, int b)
{
    return (fact[a]-fact[a-b]-fact[b]);
}

int main()
{
    for(int i = 1; i<=2e5; i++)
        fact[i] = fact[i-1]+log(i);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> w >> h >> l >> u >> r >> d;
        ans = 0;
        for(int x = r+1, y = u-1; x<=w&&y>0; x++, y--)
        {
            if(x==w)
            {
                double prob = 0;
                for(int i = 1; i<=y; i++)
                    prob+=exp(ncr(w+i-3,w-2)-(w+i-3)*log(2));
                ans+=prob/2;
            }
            else
                ans+=exp(ncr(x+y-2,x-1)-(x+y-2)*log(2));
        }
        for(int x = l-1, y = d+1; x>0&&y<=h; x--, y++)
        {
            if(y==h)
            {
                double prob = 0;
                for(int i = 1; i<=x; i++)
                    prob+=exp(ncr(h+i-3,h-2)-(h+i-3)*log(2));
                ans+=prob/2;
            }
            else
                ans+=exp(ncr(x+y-2,x-1)-(x+y-2)*log(2));
        }
        cout << "Case #" << _ << ": " << fixed << setprecision(9) << ans << endl;
    }
}
