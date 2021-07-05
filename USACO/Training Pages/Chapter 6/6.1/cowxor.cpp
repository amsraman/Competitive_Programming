/*
ID: adityasund1
TASK: cowxor
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n, a[100000], trie[(1<<20)][2], sz, xr[100000], ans, ind1, ind2;

void add(int x)
{
    int cur = 0;
    for(int i = 20; i>=0; i--)
    {
        int next = bool((1<<i)&x);
        if(!trie[cur][next])
            trie[cur][next] = ++sz;
        cur = trie[cur][next];
    }
}

int best(int x)
{
    int cur = 0, ret = 0;
    for(int i = 20; i>=0; i--)
    {
        bool opt = ((1<<i)&x);
        if((opt||(!opt&&!trie[cur][1]))&&(trie[cur][0]))
            cur = trie[cur][0];
        else
            ret+=(1<<i), cur = trie[cur][1];
    }
    return ret;
}

int main()
{
    freopen("cowxor.in","r",stdin);
    freopen("cowxor.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    add(0);
    for(int i = 0; i<n; i++)
    {
        if(i!=0) xr[i] = xr[i-1];
        xr[i]^=a[i];
        if((xr[i]^best(xr[i]))>ans)
            ans = (xr[i]^best(xr[i])), ind1 = best(xr[i]), ind2 = i;
        add(xr[i]);
    }
    for(int i = n-1; i>=0; i--)
    {
        if((xr[i]==ind1)&&(i<=ind2))
        {
            ind1 = i+1;
            break;
        }
    }
    cout << ans << " " << min(ind1,ind2)+1 << " " << ind2+1 << endl;
}