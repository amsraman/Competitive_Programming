#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, m, k, a[50];
map<multiset<int>,double> dp;

double solve(multiset<int> ms, int num)
{
    if(num==n)
        return 0;
    if(dp.count(ms))
        return dp[ms];
    double ans = 1, bad = 0;
    set<pair<int,int>> st;
    vector<int> vec;
    for(auto x: ms)
        st.insert({x,ms.count(x)}), vec.push_back(x);
    for(int cur = m-1; cur>=0; cur--)
    {
        while(cur<m-1&&vec[cur]==vec[cur+1])
            cur--;
        if(vec[cur]==a[cur])
            st.erase({vec[cur],ms.count(vec[cur])}), bad+=ms.count(vec[cur]);
    }
    for(auto x: st)
    {
        ms.erase(ms.find(x.f));
        ms.insert(x.f+1);
        ans+=solve(ms,num+1)*x.s/m;
        ms.erase(ms.find(x.f+1));
        ms.insert(x.f);
    }
    return dp[ms] = ans*m/(m-bad);
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> m >> k;
        for(int i = 0; i<k; i++)
            cin >> a[i];
        for(int i = k; i<m; i++)
            a[i] = 0;
        sort(a,a+m);
        multiset<int> ms;
        for(int i = 0; i<m; i++)
            ms.insert(0);
        cout << "Case #" << _ << ": " << fixed << setprecision(9) << solve(ms,0) << endl;
        dp.clear();
    }
}
