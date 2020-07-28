#include <bits/stdc++.h>

using namespace std;

int t, n, a, ans[100000];
int bit[100001];

int sum(int x)
{
    x++;
    int ret = 0;
    while(x>0)
        ret+=bit[x], x-=(x&(-x));
    return ret;
}

void update(int k)
{
    k++;
    while(k<=100000)
        bit[k]++, k+=(k&(-k));
}

int main()
{
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        cin >> n;
        memset(bit,0,sizeof(bit));
        for(int i = 0; i<n; i++)
        {
            cin >> a;
            update(100000-a);
            int lo = 0, hi = 99999;
            while(lo<hi)
            {
                int mid = (lo+hi)/2;
                if(sum(mid)+mid-100000>=0) hi = mid;
                else lo = mid+1;
            }
            ans[i] = 100000-lo;
        }
        cout << "Case #" << z+1 << ": ";
        for(int i = 0; i<n; i++) cout << ans[i] << " ";
        cout << endl;
    }
}
