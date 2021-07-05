#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, h[750][750], on[750][750], link[750*750], sz[750*750], num[750*750];
ll ans;
pair<int,int> dir[4] = {{-1,0},{0,1},{1,0},{0,-1}}, dir2[4] = {{0,0},{0,1},{1,0},{1,1}};
pair<int,pair<int,int>> ord[750*750];

int conv(int x, int y)
{
    return n*x+y;
}

bool ok(int x, int y, int dx, int dy)
{
    return (x+dx>=0&&x+dx<n&&y+dy>=0&&y+dy<n);
}

bool block(int x, int y)
{
    for(pair<int,int> d: dir2)
        if(!ok(x,y,d.f,d.s)||on[x+d.f][y+d.s]==0)
            return false;
    return true;
}

int f(int x)
{
    return (x==link[x]?x:link[x]=f(link[x]));
}

void unite(int x, int y)
{
    x = f(x), y = f(y);
    if(sz[x]<sz[y])
        swap(x,y);
    link[y] = x, sz[x]+=sz[y], num[x]+=(num[y]-1);
}

int main()
{
    freopen("valleys.in","r",stdin);
    freopen("valleys.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> h[i][j];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            ord[conv(i,j)] = {h[i][j],{i,j}};
    sort(ord,ord+n*n);
    for(int i = 0; i<n*n; i++)
        link[i] = i, sz[i] = 1;
    for(int i = 0, tmp; i<n*n; i++)
    {
        for(pair<int,int> d: dir)
        {
            int nx = ord[i].s.f+d.f, ny = ord[i].s.s+d.s;
            if(ok(ord[i].s.f,ord[i].s.s,d.f,d.s)&&on[nx][ny]==1&&f(conv(nx,ny))!=f(conv(ord[i].s.f,ord[i].s.s)))
                unite(conv(ord[i].s.f,ord[i].s.s),conv(nx,ny));
        }
        tmp = f(conv(ord[i].s.f,ord[i].s.s)), on[ord[i].s.f][ord[i].s.s] = 1;
        for(pair<int,int> d: dir)
            if(ok(ord[i].s.f,ord[i].s.s,d.f,d.s))
                num[tmp]+=on[ord[i].s.f+d.f][ord[i].s.s+d.s];
        for(pair<int,int> d: dir2)
            if(block(ord[i].s.f-d.f,ord[i].s.s-d.s))
                --num[tmp];
        if(num[tmp]==0)
            ans+=sz[tmp];
    }
    cout << ans << endl;
}