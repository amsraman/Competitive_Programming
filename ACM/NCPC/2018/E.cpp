#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n, m, d;
array<int,10> init;
map<array<int,10>,ld> dp;

ld f(array<int,10> x, int moves_left)
{
    sort(x.begin(),x.begin()+n);
    sort(x.begin()+n,x.begin()+n+m);
    if(dp.count(x))
        return dp[x];
    int opp = 0, tot = 0;
    ld ret = 0;
    for(int i = 0; i<n+m; i++)
    {
        if(x[i]>0)
            ++tot;
        if(i>=n)
            opp+=(x[i]>0);
    }
    if(opp==0)
        return dp[x] = 1;
    if(moves_left==0)
        return dp[x] = 0;
    for(int i = 0; i<n+m; i++)
        if(x[i]>0)
            --x[i], ret+=f(x,moves_left-1), ++x[i];
    return dp[x] = ret/(ld)tot;
}

int main()
{
    cin >> n >> m >> d;
    for(int i = 0; i<n; i++)
        cin >> init[i];
    for(int i = 0; i<m; i++)
        cin >> init[i+n];
    cout << fixed << setprecision(8) << f(init,d) << endl;
}