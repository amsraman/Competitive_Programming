#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, p, w, x, y, z, best[100000];
pair<pair<int,int>,pair<int,int> > in[200000];
map<int,int> m;

void update(int a, int b)
{
    map<int,int>::iterator it = m.upper_bound(a);
    if(it!=m.begin()) it--;
    if((it->f<=a)&&(it->s<=b)) return;
    it = m.upper_bound(a);
    while((it!=m.end())&&(it->s>=b)) m.erase(it++);
    m[a] = b;
}

int main()
{
    freopen("boards.in","r",stdin);
    freopen("boards.out","w",stdout);
    cin >> n >> p;
    for(int i = 0; i<p; i++)
    {
        cin >> w >> x >> y >> z;
        in[2*i] = {{w,x},{i,1}};
        in[2*i+1] = {{y,z},{i,0}};
    }
    sort(in,in+2*p);
    for(int i = 0; i<2*p; i++)
    {
        if(in[i].s.s)
        {
            best[in[i].s.f] = in[i].f.f+in[i].f.s;
            map<int,int>::iterator it = m.upper_bound(in[i].f.s);
            if(it==m.begin()) continue;
            else if(it==m.end()) it--;
            else if(it->first!=in[i].f.s) it--;
            best[in[i].s.f]+=(it->second);
        }
        else
            update(in[i].f.s,best[in[i].s.f]-in[i].f.f-in[i].f.s);
    }
    cout << 2*n+((--m.end())->s) << endl;
}
