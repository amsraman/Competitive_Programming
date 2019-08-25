#include <fstream>
#include <iostream>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, a, b, sp[100000];
ll pre[100001], spre[100001], ans;
pair<int,int> in[100000];

ll modx(ll a){return (a%MOD+MOD)%MOD;}

int main()
{
    ifstream infile("sprinklers.in");
    ofstream outfile("sprinklers.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        sp[b] = a;
    }
    in[0].first = sp[0], in[n-1].second = sp[n-1];
    for(int i = 1; i<n; i++)
    {
        in[i].first = min(in[i-1].first,sp[i]);
    }
    for(int i = n-2; i>=0; i--)
    {
        in[i].second = max(in[i+1].second,sp[i]);
    }
    int cur = n-1;
    for(int i = 0; i<n; i++)
    {
        while(cur>=in[i].first)
        {
            pre[cur] = i;
            cur--;
        }
    }
    spre[n-1] = pre[n-1];
    for(int i = n-2; i>=0; i--)
    {
        spre[i] = modx(spre[i+1]+(pre[i])*ll(n-i));
        pre[i] = modx(pre[i]+pre[i+1]);
    }
    for(int i = 0; i<n-1; i++)
    {
        ll p1 = ll(in[i].first), p2 = ll(min(in[i+1].second,in[i].second));
        ans = modx(ans+modx(max(p2-p1,ll(0))*(p2-p1+1)/2)*ll(i+1)-modx((spre[p1]-spre[p2])-(pre[p1]-pre[p2])*ll(n-p2)));
    }
    outfile << ans << endl;
}
