#include <fstream>
#include <iostream>

using namespace std;

int n, b, f[250], m[250], ans;
pair<int,int> s[250];
bool v[250][250] = {false};

void dfs(int x, int y)
{
    if(v[x][y])
    {
        return;
    }
    v[x][y] = true;
    if(f[x]>s[y].first)
    {
        return;
    }
    if(x==n-1)
    {
        ans = min(ans,y);
        return;
    }
    for(int i = min(n-x-1,s[y].second); i>=0; i--)
    {
        dfs(x+i,y);
    }
    for(int i = y; i<b; i++)
    {
        if(s[i].first>=f[x])
        {
            dfs(x,i);
        }
    }
}

int main()
{
    ifstream infile("snowboots.in");
    ofstream outfile("snowboots.out");
    infile >> n >> b;
    ans = b+1;
    for(int i = 0; i<n; i++)
    {
        infile >> f[i];
    }
    for(int i = 0; i<b; i++)
    {
        infile >> s[i].first >> s[i].second;
    }
    dfs(0,0);
    outfile << ans << endl;
}
