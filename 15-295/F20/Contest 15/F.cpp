#include <bits/stdc++.h>
#define f first
#define s second
#define PI 4*atan(1)

using namespace std;

int n;
double d, ans;
vector<pair<long double,long double>> p;
set<pair<long double,long double>> in;
pair<long double,long double> center, hull[400000];
pair<long double,int> ang[400000];

void ins(long double a, long double b)
{
    p.push_back({a,b});
    in.insert({a,b});
}

int main()
{
    cin >> n >> d;
    for(int i = 0; i<n; i++)
    {
        pair<long double,long double> tmp;
        cin >> tmp.f >> tmp.s;
        if(!in.count({tmp.f+d,tmp.s}))
            ins(tmp.f+d,tmp.s);
        if(!in.count({tmp.f-d,tmp.s}))
            ins(tmp.f-d,tmp.s);
        if(!in.count({tmp.f,tmp.s+d}))
            ins(tmp.f,tmp.s+d);
        if(!in.count({tmp.f,tmp.s-d}))
            ins(tmp.f,tmp.s-d);
    }
    n = p.size();
    //I need a better convex hull implementation...
    for(int i = 0; i<n; i++)
    {
        center.f+=p[i].f;
        center.s+=p[i].s;
    }
    center.f/=(long double)(n);
    center.s/=(long double)(n);
    for(int i = 0; i<n; i++)
    {
        ang[i].f = (atan2(p[i].s-center.s,p[i].f-center.f)<0)?atan2(p[i].s-center.s,p[i].f-center.f)+2*PI:atan2(p[i].s-center.s,p[i].f-center.f);
        ang[i].s = i;
    }
    sort(ang,ang+n);
    hull[0] = {p[ang[0].s].f,p[ang[0].s].s};
    hull[1] = {p[ang[1].s].f,p[ang[1].s].s};
    int begh = 0, endh = 1;
    for(int i = 2; i<n; i++)
    {
        while((endh>0)&&((hull[endh].f-hull[endh-1].f)*(p[ang[i].s].s-hull[endh].s)-(hull[endh].s-hull[endh-1].s)*(p[ang[i].s].f-hull[endh].f)<0))
            endh--;
        endh++;
        hull[endh] = {p[ang[i].s].f,p[ang[i].s].s};
    }
    while(((hull[begh+1].f-hull[begh].f)*(hull[begh].s-hull[endh].s)-(hull[begh+1].s-hull[begh].s)*(hull[begh].f-hull[endh].f)>0)||((hull[begh].f-hull[endh].f)*(hull[endh].s-hull[endh-1].s)-(hull[begh].s-hull[endh].s)*(hull[endh].f-hull[endh-1].f)>0))
    {
        if((hull[begh+1].f-hull[begh].f)*(hull[begh].s-hull[endh].s)-(hull[begh+1].s-hull[begh].s)*(hull[begh].f-hull[endh].f)>0)
            begh++;
        else
            endh--;
    }
    ans = sqrt((hull[endh].f-hull[begh].f)*(hull[endh].f-hull[begh].f)+(hull[endh].s-hull[begh].s)*(hull[endh].s-hull[begh].s));
    for(int i = begh; i<endh; i++)
        ans+=sqrt((hull[i+1].f-hull[i].f)*(hull[i+1].f-hull[i].f)+(hull[i+1].s-hull[i].s)*(hull[i+1].s-hull[i].s));
    cout << fixed << setprecision(10) << ans << endl;
}