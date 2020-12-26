#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, c, cc, comp[1000], tmp[1000], ans;
ll x_xor[1000], y_xor[1000];
pair<ll,ll> cows[1000];
pair<pair<ll,ll>,pair<ll,ll>> lines[1000];
map<pair<ll,ll>,ll> edge_xor;
map<pair<int,int>,int> num; //because I can't be bothered to evaluate polygon levels
bool vis[1000];

bool cross(ll a, ll b, ll c, ll d)
{
    return (a*d>=b*c);
}

bool sect(pair<pair<ll,ll>,pair<ll,ll>> a, pair<pair<ll,ll>,pair<ll,ll>> b)
{
    bool ck1 = cross(a.f.f-b.f.f,a.f.s-b.f.s,b.f.f-b.s.f,b.f.s-b.s.s)^cross(a.s.f-b.f.f,a.s.s-b.f.s,b.f.f-b.s.f,b.f.s-b.s.s);
    bool ck2 = cross(b.f.f-a.f.f,b.f.s-a.f.s,a.f.f-a.s.f,a.f.s-a.s.s)^cross(b.s.f-a.f.f,b.s.s-a.f.s,a.f.f-a.s.f,a.f.s-a.s.s);
    return ck1&&ck2;
    //not really a complete intersection check but hey... these segments can't be parallel anyway so we're fine :^)
}

int main()
{
    cin >> n >> c;
    for(int i = 0; i<n; i++)
    {
        cin >> lines[i].f.f >> lines[i].f.s >> lines[i].s.f >> lines[i].s.s;
        x_xor[i] = lines[i].f.f^lines[i].s.f;
        y_xor[i] = lines[i].f.s^lines[i].s.s;
        edge_xor[lines[i].f]^=i, edge_xor[lines[i].s]^=i;
    }
    for(int i = 0; i<c; i++)
        cin >> cows[i].f >> cows[i].s;
    for(int i = 0; i<n; i++)
        if(!vis[i])
        {
            int cur_edge = i, curx = lines[i].f.f, cury = lines[i].f.s;
            while(!vis[cur_edge])
            {
                vis[cur_edge] = true, comp[cur_edge] = cc;
                curx^=x_xor[cur_edge], cury^=y_xor[cur_edge];
                cur_edge^=edge_xor[{curx,cury}];
            }
            ++cc;
        }
    for(int i = 0; i<c; i++)
    {
        fill(tmp,tmp+cc,0);
        pair<pair<ll,ll>,pair<ll,ll>> cur = pair<pair<ll,ll>,pair<ll,ll>>(cows[i],{1000003,1000003});
        for(int j = 0; j<n; j++)
            if(sect(cur,lines[j]))
                tmp[comp[j]]++;
        int ind = -1, cnt = 0;
        for(int j = 0; j<cc; j++)
            if(tmp[j]&1)
                ind = j, cnt++;
        num[{ind,cnt}]++;
    }
    for(auto x: num)
        ans = max(ans,x.s), c-=x.s;
    cout << max(ans,c) << endl;
}
