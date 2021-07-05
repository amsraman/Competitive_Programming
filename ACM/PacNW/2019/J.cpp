#include <bits/stdc++.h>
typedef long double ld;
#define PI acos(-1)

using namespace std;

int n;
ld cur, cur_slope, ans, pv;
array<ld,3> ships[100000];
map<ld,ld> delta;
set<ld> points;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> ships[i][0] >> ships[i][1] >> ships[i][2];
    //Assume you're starting just before 0
    for(int i = 0; i<n; i++)
    {
        ld dist = min((ld)PI,ships[i][0]/ships[i][1]), ang1 = ships[i][2]-dist, ang2 = ships[i][2]+dist;
        if(ang1<0&&ships[i][2]>=0)
            cur_slope+=ships[i][1];
        if(ships[i][2]<2*PI&&ang2>=2*PI)
            cur_slope-=ships[i][1];
        if(ang1<0)
            ang1+=2*PI;
        if(ang2>=2*PI)
            ang2-=2*PI;
        if(ships[i][0]/ships[i][1]>=PI)
            ang2 = ang1;
        delta[ang1]+=ships[i][1], delta[ships[i][2]]-=2*ships[i][1], delta[ang2]+=ships[i][1];
        points.insert(ships[i][2]), points.insert(ang1), points.insert(ang2);
        cur+=max((ld)0.0,ships[i][0]-ships[i][1]*min(ships[i][2],2*PI-ships[i][2]));
    }
    ans = cur;
    for(ld i: points)
    {
        cur+=cur_slope*(i-pv);
        ans = max(ans,cur);
        cur_slope+=delta[i];
        pv = i;
    }
    cout << fixed << setprecision(9) << ans << endl;
}
