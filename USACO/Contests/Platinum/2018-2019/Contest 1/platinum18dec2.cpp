#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN (1<<17)

using namespace std;

int n, in[100000], lis[100000], seg[2*MAXN], curp = -1, curl, ans;
long long k, dp[100000], segdp[2*MAXN];
vector<int> vlis[100000];
vector<pair<pair<int,int>,int> > vec;
bool v[100000];

int qmax(int x)
{
    int low = x+MAXN, high = n+MAXN-1, ret = 0;
    while(low<=high)
    {
        if(high%2==0) ret = max(ret,seg[high]), high--;
        if(low%2==1) ret = max(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

long long qsum(int x)
{
    int low = x+MAXN, high = n+MAXN-1;
    long long ret = 0;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret+segdp[high],k+1), high--;
        if(low%2==1) ret = min(ret+segdp[low],k+1), low++;
        low/=2, high/=2;
    }
    return ret;
}

void umax(int p, int x)
{
    p+=MAXN, seg[p] = x;
    while(p>1)
    {
        p/=2;
        seg[p] = max(seg[2*p],seg[2*p+1]);
    }
}

void usum(int p, long long x)
{
    p+=MAXN, segdp[p] = x;
    while(p>1)
    {
        p/=2;
        segdp[p] = min(segdp[2*p]+segdp[2*p+1],k+1);
    }
}

int main()
{
    ifstream infile("itout.in");
    ofstream outfile("itout.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++) infile >> in[i];
    for(int i = n-1; i>=0; i--)
    {
        lis[i] = qmax(in[i])+1;
        curl = ans = max(ans,lis[i]);
        if(lis[i]==1) dp[i] = 1;
        umax(in[i]-1,lis[i]);
        vlis[lis[i]-1].push_back(i);
        vec.push_back(make_pair(make_pair(-lis[i],-in[i]),i));
    }
    sort(vec.begin(),vec.end());
    for(int i = 1; i<n; i++)
    {
        int p1 = 0;
        for(int j = 0; j<vlis[i].size(); j++)
        {
            while((p1!=vlis[i-1].size())&&(vlis[i-1][p1]>vlis[i][j])) usum(in[vlis[i-1][p1]]-1,dp[vlis[i-1][p1]]), p1++;
            dp[vlis[i][j]] = qsum(in[vlis[i][j]]);
        }
        for(int j = 0; j<vlis[i-1].size(); j++) usum(in[vlis[i-1][j]]-1,0);
    }
    for(int i = 0; i<n; i++)
    {
        if((vec[i].first.first==-curl)&&(vec[i].second>curp))
        {
            if(dp[vec[i].second]<k) k-=dp[vec[i].second];
            else v[-vec[i].first.second-1] = true, curl--, curp = vec[i].second;
        }
    }
    outfile << n-ans << endl;
    for(int i = 0; i<n; i++)
    {
        if(!v[i]) outfile << i+1 << endl;
    }
}
