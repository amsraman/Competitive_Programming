#include <bits/stdc++.h>

using namespace std;

int n, k, sz[5], hit, in, ans;
bool blocked[5][5], placed[5];
string grid[5];

bool open(int a, int b, int c, int d)
{
    if(c>n||d>n)
        return false;
    for(int i = a; i<c; i++)
        for(int j = b; j<d; j++)
            if(blocked[i][j])
                return false;
    return true;
}

void place(int a, int b, int c, int d, bool e)
{
    in+=(2*(int)e-1);
    for(int i = a; i<c; i++)
        for(int j = b; j<d; j++)
        {
            blocked[i][j] = e;
            hit-=((2*(int)e-1)*(grid[i][j]=='O'));
        }
}

void gen(int x, int y)
{
    if(x==n)
    {
        if(hit==0&&in==k)
            ++ans;
        return;
    }
    gen(x+(y+1)/n,(y+1)%n);
    if(blocked[x][y])
        return;
    for(int i = 0; i<k; i++)
        if(!placed[i])
        {
            placed[i] = true;
            if(open(x,y,x+sz[i],y+1))
            {
                place(x,y,x+sz[i],y+1,1);
                gen(x+(y+1)/n,(y+1)%n);
                place(x,y,x+sz[i],y+1,0);
            }
            if(sz[i]>1&&open(x,y,x+1,y+sz[i]))
            {
                place(x,y,x+1,y+sz[i],1);
                gen(x+(y+1)/n,(y+1)%n);
                place(x,y,x+1,y+sz[i],0);
            }
            placed[i] = false;
        }
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    for(int i = 0; i<k; i++)
        cin >> sz[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            blocked[i][j] = grid[i][j]=='X';
            hit+=(grid[i][j]=='O');
        }
    gen(0,0);
    cout << ans << endl;
}