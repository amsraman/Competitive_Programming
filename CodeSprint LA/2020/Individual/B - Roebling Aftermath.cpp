#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, r, mx;
pair<int,int> st;
char in[1000000];
bool vis[1000000];

int conv(int a, int b)
{
    return m*a+b;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            cin >> in[conv(i,j)];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
        {
            if(in[conv(i,j)]=='C')
                st = {i,j};
            if(in[conv(i,j)]=='R')
                r = j;
        }
    queue<pair<int,int> > q;
    q.push(st), vis[conv(st.f,st.s)] = true;
    while(!q.empty())
    {
        int x = q.front().f, y = q.front().s;
        q.pop();
        mx = max(mx,y);
        if((x>0)&&(in[conv(x-1,y)]!='X')&&(!vis[conv(x-1,y)]))
            q.push({x-1,y}), vis[conv(x-1,y)] = true;
        if((y>0)&&(in[conv(x,y-1)]!='X')&&(!vis[conv(x,y-1)])&&(in[conv(x,y)]!='R'))
            q.push({x,y-1}), vis[conv(x,y-1)] = true;
        if((x<n-1)&&(in[conv(x+1,y)]!='X')&&(!vis[conv(x+1,y)]))
            q.push({x+1,y}), vis[conv(x+1,y)] = true;
        if((y<m-1)&&(in[conv(x,y+1)]!='X')&&(!vis[conv(x,y+1)]))
            q.push({x,y+1}), vis[conv(x,y+1)] = true;
        if((x>0)&&(y>0)&&(in[conv(x-1,y-1)]!='X')&&(!vis[conv(x-1,y-1)])&&(in[conv(x,y)]!='R'))
            q.push({x-1,y-1}), vis[conv(x-1,y-1)] = true;
        if((x>0)&&(y<m-1)&&(in[conv(x-1,y+1)]!='X')&&(!vis[conv(x-1,y+1)]))
            q.push({x-1,y+1}), vis[conv(x-1,y+1)] = true;
        if((x<n-1)&&(y>0)&&(in[conv(x+1,y-1)]!='X')&&(!vis[conv(x+1,y-1)])&&(in[conv(x,y)]!='R'))
            q.push({x+1,y-1}), vis[conv(x+1,y-1)] = true;
        if((x<n-1)&&(y<m-1)&&(in[conv(x+1,y+1)]!='X')&&(!vis[conv(x+1,y+1)]))
            q.push({x+1,y+1}), vis[conv(x+1,y+1)] = true;
    }
    cout << ((mx>r)?("yes"):("no")) << endl;
}
