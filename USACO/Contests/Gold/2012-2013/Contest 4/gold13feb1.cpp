#include <bits/stdc++.h>

using namespace std;

int n, k, cows[15][15], sz[(1<<15)], group[15];

bool check(int x, int y)
{
    int ind = 0, cur = 0, ret = sz[x]-1;
    memset(group,0,sizeof(group));
    for(int i = 0; i<n; i++)
    {
        ind = 0;
        bool stop = false;
        for(int j = 0; j<n; j++)
        {
            cur+=cows[i][j];
            if((1<<j)&x)
            {
                if(cur>y)
                    return false;
                if((group[ind]+cur>y)&&(!stop))
                    stop = true, ret++;
                group[ind]+=cur, ind++, cur = 0;
            }
        }
        if(!stop)
            continue;
        cur = ind = 0;
        for(int j = 0; j<n; j++)
        {
            cur+=cows[i][j];
            if((1<<j)&x)
                group[ind] = cur, ind++, cur = 0;
        }
    }
    return (ret<=k);
}

bool ok(int x)
{
    for(int i = 0; i<(1<<(n-1)); i++)
        if(check(i+(1<<(n-1)),x))
            return true;
    return false;
}

int main()
{
    freopen("partition.in","r",stdin);
    freopen("partition.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> cows[i][j];
    for(int i = 1; i<(1<<n); i++)
        sz[i] = sz[i-(i&(-i))]+1;
    int l = 0, g = 225000;
    while(l<g)
    {
        int mid = (l+g)/2;
        if(ok(mid)) g = mid;
        else l = mid+1;
    }
    cout << g << endl;
}
