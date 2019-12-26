#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

using namespace std;

int n;
ld y, inc, s, b, p1, p2, grad, cur, ans;
pair<pair<ld,ld>,ld> in[3000];
vector<pair<pair<ld,ld>,ld> > vec;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> y >> inc >> s >> b;
        in[3*i] = {{b,inc},s};
        if(inc!=0)
            in[3*i+1] = {{b+y,-2*inc},0}, in[3*i+2] = {{b+2*y+(s/inc),inc},0};
    }
    sort(in,in+3*n);
    for(int i = 0; i<3*n; i++)
    {
        p1+=in[i].first.second, p2+=in[i].second;
        if((i==3*n-1)||(in[i].first.first!=in[i+1].first.first))
        {
            vec.push_back({{in[i].first.first,p1},p2});
            p1 = 0, p2 = 0;
        }
    }
    for(int i = 0; i<vec.size(); i++)
    {
        cur+=vec[i].second;
        if(i!=0)
            cur+=grad*(vec[i].first.first-vec[i-1].first.first);
        grad+=vec[i].first.second;
        ans = max(ans,ld(ll(cur+0.1)));
    }
    cout << fixed << setprecision(0) << ans << endl;
}
