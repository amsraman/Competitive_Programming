#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, n;
ll v, r, tv, tr, ans;
char o;
map<int,int> pr;
vector<pair<ll,ll>> lv, gv;

ll exp(ll a, int b)
{
    ll ret = 1;
    while(b>0)
    {
        if(b&1)
            ret*=a;
        a*=a, b/=2;
    }
    return ret;
}

int main()
{
    freopen("integers_as_a_service_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        ans = 1;
        for(int i = 0; i<n; i++)
        {
            cin >> o >> v >> r;
            vector<pair<int,int>> v1, v2;
            tv = v, tr = r;
            for(int j = 2; j*j<=tv; j++)
                if(tv%j==0)
                {
                    int num = 0;
                    while(tv%j==0)
                        tv/=j, num++;
                    v1.push_back({j,num});
                }
            for(int j = 2; j*j<=tr; j++)
                if(tr%j==0)
                {
                    int num = 0;
                    while(tr%j==0)
                        tr/=j, num++;
                    v2.push_back({j,num});
                }
            if(tv!=1)
                v1.push_back({tv,1});
            if(tr!=1)
                v2.push_back({tr,1});
            if((o=='G')&&(v%r==0))
            {
                for(int j = 0, k = 0; j<v1.size(); j++, k++)
                    if((k>=v2.size())||(k<v2.size()&&(v2[k].f!=v1[j].f)))
                        v2.push_back({v1[j].f,0}), k--;
                sort(v2.begin(),v2.end());
                for(auto x:v2)
                    pr[x.f] = max(pr[x.f],x.s);
            }
            else if(r%v==0)
            {
                for(int j = 0, k = 0; j<v2.size(); j++, k++)
                    if((k>=v1.size())||(k<v1.size()&&(v1[k].f!=v2[j].f)))
                        v1.push_back({v2[j].f,0}), k--;
                sort(v1.begin(),v1.end());
                for(int j = 0; j<v1.size(); j++)
                    if(v1[j].s!=v2[j].s)
                        pr[v2[j].f] = max(pr[v2[j].f],v2[j].s);
            }
            if(o=='G')
                gv.push_back({v,r});
            if(o=='L')
                lv.push_back({v,r});
        }
        for(auto x:pr)
            ans*=exp(x.f,x.s), pr[x.f] = 0;
        for(auto x:lv)
            if((ans!=-1)&&(ans*x.f/__gcd(ans,x.f)!=x.s))
                ans = -1;
        for(auto x:gv)
            if((ans!=-1)&&(__gcd(ans,x.f)!=x.s))
                ans = -1;
        cout << "Case #" << _ << ": " << (ans<=1e9?ans:-1) << endl;
        gv.clear(), lv.clear();
    }
}
