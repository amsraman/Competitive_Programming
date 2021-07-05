#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007

using namespace std;

int n, c[16][16], cn[(1<<16)], uc[(1<<16)], tot[(1<<16)];

int mul(int x, int y)
{
    return ((ll)x*y)%MOD;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> c[i][j];
    for(int i = 1, fst; i<(1<<n); i++)
    {
        tot[i] = 1;
        for(int j = 0; j<n; j++)
            for(int k = j+1; k<n; k++)
                if(((1<<j)&i)&&((1<<k)&i))
                    tot[i] = mul(tot[i],c[j][k]+1);
        for(int j = n-1; j>=0; j--)
            if((1<<j)&i)
                fst = j;
        for(int j = i-1; j>0; j = (j-1)&i)
            if((1<<fst)&j)
                uc[i] = (uc[i]+mul(cn[j],tot[i^j]))%MOD;
        cn[i] = (tot[i]-uc[i]+MOD)%MOD;
    }
    cout << cn[(1<<n)-1] << endl;
}