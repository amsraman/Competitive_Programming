#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second
#define PI 4*atan(1)

using namespace std;

int n, nxt[2000][2000], num[2000], ans;
pair<int,int> p[2000];
bool seen[2000][2000][2];

bool side(ld x)
{
    if(x<2*PI&&x>PI)
        return 1;
    return 0;
}

ld ang(int ax, int ay, int bx, int by)
{
    ld ret = atan2(ax*by-ay*bx,ax*bx+ay*by);
    if(ret<0)
        ret+=PI;
    return ret;
}

int mx(int x, int y)
{
    int p1 = x, p2 = y, ret = 0;
    ld turn = 0;
    fill(num,num+n,0);
    while(1)
    {
        num[p2]++, turn+=ang(p[p1].f-p[p2].f,p[p1].s-p[p2].s,p[nxt[p2][p1]].f-p[p2].f,p[nxt[p2][p1]].s-p[p2].s);
        p1 = nxt[p2][p1], swap(p1,p2);
        if(p1==x&&p2==y&&abs(turn-2*PI)<=1e-5)
            break;
        if(seen[p1][p2][side(turn)])
            return 0;
        seen[p1][p2][side(turn)] = true;
    }
    for(int i = 0; i<n; i++)
        ret = max(ret,num[i]);
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i].f >> p[i].s;
    for(int i = 0; i<n; i++)
    {
        vector<pair<ld,int>> tmp;
        for(int j = 0; j<n; j++)
            if(i!=j)
                tmp.push_back({atan2(p[j].s-p[i].s,p[j].f-p[i].f),j});
        for(int i = 0; i<n-1; i++)
        {
            if(tmp[i].f<-PI/2)
                tmp[i].f+=PI;
            if(tmp[i].f>=PI/2)
                tmp[i].f-=PI;
        }
        sort(tmp.begin(),tmp.end());
        for(int j = 0; j<n-1; j++)
            nxt[i][tmp[j].s] = tmp[(j+1)%(n-1)].s;
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(i!=j)
                ans = max(ans,mx(i,j));
    cout << ans << endl;
}