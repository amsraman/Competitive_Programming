#include <bits/stdc++.h>

using namespace std;

int n, nc, nxt[200], ans;
map<string,int> ind;
string tr, ob1, ob2;

int f(int x)
{
    int p1 = nxt[x], p2 = nxt[nxt[x]];
    while(p1!=p2)
        p1 = nxt[p1], p2 = nxt[nxt[p2]];
    p2 = nxt[p2];
    int ret = 1;
    while(p1!=p2)
        p2 = nxt[p2], ++ret;
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> tr >> ob1 >> ob2;
        if(!ind.count(ob1))
            ind[ob1] = ++nc;
        if(!ind.count(ob2))
            ind[ob2] = ++nc;
        nxt[ind[ob1]] = ind[ob2];
    }
    for(int i = 0; i<=nc; i++)
        ans = max(ans,f(i));
    if(ans==1)
        cout << "No trades possible" << endl;
    else
        cout << ans << endl;
}