#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, total_count;
ll base, total_cost;
vector<int> p[100000];

void get_num(int pf, ll budget)
{
    if(pf<0) 
    {
        ++total_count;
        return;
    }
    int lb = 0, ub = pf;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(p[mid][0]<=budget)
            lb = mid;
        else
            ub = mid-1;
    }
    get_num(ub-1,budget);
    for(int i = 0; i<p[ub].size(); i++)
    {
        if(total_count>=k||p[ub][i]>budget)
            return;
        get_num(ub-1,budget-p[ub][i]);
    }
}

void get_cost(int pf, ll budget, ll cur_cost)
{
    if(pf<0)
    {
        total_cost+=(base+cur_cost);
        return;
    }
    int lb = 0, ub = pf;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(p[mid][0]<=budget)
            lb = mid;
        else
            ub = mid-1;
    }
    for(int i = 0; i<p[ub].size(); i++)
        if(budget>=p[ub][i])
            get_cost(ub-1,budget-p[ub][i],cur_cost+p[ub][i]);
    get_cost(ub-1,budget,cur_cost);
}

int main()
{
    freopen("roboherd.in","r",stdin);
    freopen("roboherd.out","w",stdout);
    cin >> n >> k;
    for(int i = 0, m; i<n; i++)
    {
        cin >> m;
        vector<int> v(m);
        for(int j = 0; j<m; j++)
            cin >> v[j];
        sort(v.begin(),v.end()), base+=v[0];
        if(v.size()==1)
        {
            --i, --n;
            continue;
        }
        for(int j = 1; j<m; j++)
            p[i].push_back(v[j]-v[0]);
    }
    sort(p,p+n);
    ll lb = 0, ub = 1e15;
    while(lb<ub)
    {
        ll mid = (lb+ub)/2;
        total_count = 0, get_num(n-1,mid);
        if(total_count<k)
            lb = mid+1;
        else
            ub = mid;
    }
    total_count = 0, get_num(n-1,ub-1);
    get_cost(n-1,ub-1,0);
    cout << total_cost+(ll)(k-total_count)*(base+ub) << endl;
}