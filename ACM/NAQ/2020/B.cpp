#include <bits/stdc++.h>
#define f first
#define s second
#define epsilon 1e-11
typedef long double ld;

using namespace std;

int n;
ld ans;
set<pair<ld,ld>> covered;
array<ld,3> circles[2000];

pair<ld,ld> sect(int ind1, int ind2)
{
    ld dist = sqrt((circles[ind1][0]-circles[ind2][0])*(circles[ind1][0]-circles[ind2][0])+(circles[ind1][1]-circles[ind2][1])*(circles[ind1][1]-circles[ind2][1]));
    //ind2 covers ind1
    if(circles[ind1][2]+dist<=circles[ind2][2])
        return {0,2*M_PI};
    //ind1 covers ind2 or ind1 and ind1 are disjoint
    if(circles[ind2][2]+dist<circles[ind1][2]||circles[ind1][2]+circles[ind2][2]<=dist)
        return {0,0};
    ld mid = atan2(circles[ind2][1]-circles[ind1][1],circles[ind2][0]-circles[ind1][0]);
    //LoC
    ld diff = acos((dist*dist+circles[ind1][2]*circles[ind1][2]-circles[ind2][2]*circles[ind2][2])/(2*circles[ind1][2]*dist));
    if(mid<0)
        mid+=2*M_PI;
    return {mid-diff,mid+diff};

}

void add_seg(pair<ld,ld> seg)
{
    covered.insert(seg);
    auto it = covered.find(seg), it2 = (++covered.find(seg));
    if(((it!=covered.begin())&&((--it)->s>seg.s-epsilon))||((it2!=covered.end())&&(abs(it2->f-seg.f)<epsilon))||(covered.count(seg)>1))
        covered.erase(covered.find(seg));
    else
    {
        it = ++covered.find(seg);
        while((it!=covered.end())&&(it->s<seg.s))
        {
            pair<ld,ld> temp = *it;
            it++;
            covered.erase(covered.find(temp));
        }
        pair<ld,ld> tmp = seg;
        it = (++covered.find(tmp));
        if((it!=covered.end())&&(it->f<seg.s-epsilon))
            seg.s = it->s, covered.erase(it);
        it = covered.find(tmp);
        if((it!=covered.begin())&&((--it)->s>seg.f+epsilon))
            seg.f = it->f, covered.erase(it);
        covered.erase(covered.find(tmp));
        covered.insert(seg);
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<3; j++)
            cin >> circles[i][j];
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            pair<ld,ld> cut = sect(i,j);
            if(cut.s>2*M_PI-epsilon)
                add_seg({cut.f,2*M_PI}), add_seg({0,cut.s-2*M_PI});
            else if(cut.f<epsilon)
                add_seg({cut.f+2*M_PI,2*M_PI}), add_seg({0,cut.s});
            else
                add_seg(cut);
        }        
        ld ang = 2*M_PI;
        for(pair<ld,ld> c: covered)
            ang-=(c.s-c.f);
        ans+=circles[i][2]*ang;
        covered.clear();
    }
    cout << fixed << setprecision(9) << ans << endl;
}