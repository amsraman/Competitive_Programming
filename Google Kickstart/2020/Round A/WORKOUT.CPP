#include <bits/stdc++.h>

using namespace std;

int t, n, k, m[100000];

bool ok(double x)
{
    int div = 0;
    for(int i = 0; i<n-1; i++)
        div+=(ceil((double)(m[i+1]-m[i])/x)-1);
    return (div<=k);
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n >> k;
        for(int i = 0; i<n; i++)
            cin >> m[i];
        int lb = 1, ub = 1e9;
        while(lb<ub)
        {
            int mid = (lb+ub)/2;
            if(ok(double(mid))) ub = mid;
            else lb = mid+1;
        }
        cout << "Case #" << cs+1 << ": " << ub << endl;
    }
}
