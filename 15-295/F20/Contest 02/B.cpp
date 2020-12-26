#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int w, h, n, we[200000], he[200000];
set<int> wind, hind;
multiset<ll> wc, hc;
char op;

int main()
{
    cin >> w >> h >> n;
    wc.insert(w), hc.insert(h);
    wind.insert(0), hind.insert(0);
    we[0] = w, he[0] = h;
    for(int i = 0, ct; i<n; i++)
    {
        cin >> op >> ct;
        if(op=='V')
        {
            wind.insert(ct);
            int x = *(--wind.find(ct));
            wc.erase(wc.find(we[x]-x));
            wc.insert(ct-x), wc.insert(we[x]-ct);
            we[ct] = we[x], we[x] = ct;
        }
        else
        {
            hind.insert(ct);
            int x = *(--hind.find(ct));
            hc.erase(hc.find(he[x]-x));
            hc.insert(ct-x), hc.insert(he[x]-ct);
            he[ct] = he[x], he[x] = ct;
        }
        cout << (*(--wc.end()))*(*(--hc.end())) << endl;
    }
}