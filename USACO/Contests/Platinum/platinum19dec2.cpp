#include <bits/stdc++.h>

using namespace std;

int n, q, a, b, t, type;
long long bit1[200010], bit2[200010];
pair<int,int> in[100000];
set<pair<int,int> > colors[100000];
vector<int> g[100000];

void dfs(int x, int prev)
{
    in[x].first = t++;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=prev)
            dfs(g[x][i],x);
    in[x].second = t++;
}

long long query(long long l, long long r)
{
    r++;
    long long s1 = 0, s2 = 0;
    int templ = l, tempr = r;
    while(templ>0)
        s1+=(l*bit1[templ]), s1-=bit2[templ], templ-=(templ&(-templ));
    while(tempr>0)
        s2+=(r*bit1[tempr]), s2-=bit2[tempr], tempr-=(tempr&(-tempr));
    return s2-s1;
}

void update(int l, int r, int v)
{
    l++, r+=2;
    int templ = l, tempr = r;
    while(templ<=2*n)
        bit1[templ]+=v, bit2[templ]+=(v*(l-1)), templ+=(templ&(-templ));
    while(tempr<=2*n)
        bit1[tempr]-=v, bit2[tempr]-=(v*(r-1)), tempr+=(tempr&(-tempr));
}

int main()
{
    freopen("snowcow.in","r",stdin);
    freopen("snowcow.out","w",stdout);
    cin >> n >> q;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    dfs(0,0);
    for(int i = 0; i<q; i++)
    {
        cin >> type;
        if(type==1)
        {
            cin >> a >> b;
            colors[b-1].insert(in[a-1]);
            set<pair<int,int> >::iterator it = colors[b-1].find(in[a-1]);
            if((it!=colors[b-1].begin())&&((--it)->second>in[a-1].first))
            {
                colors[b-1].erase(colors[b-1].find(in[a-1]));
                continue;
            }
            update(in[a-1].first,in[a-1].second,1);
            it = (++colors[b-1].find(in[a-1]));
            while((it!=colors[b-1].end())&&(it->second<in[a-1].second))
            {
                pair<int,int> temp = (*it);
                update(temp.first,temp.second,-1);
                it++;
                colors[b-1].erase(colors[b-1].find(temp));
            }
        }
        else
        {
            cin >> a;
            cout << query(in[a-1].first,in[a-1].second)/2 << endl;
        }
    }
}
