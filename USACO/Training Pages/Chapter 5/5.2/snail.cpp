/*
ID: adityasund1
TASK: snail
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int n, b, y, ans, dist;
pair<int,int> dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};
bool v[120][120], bar[120][120];

void dfs(int a, int b, int d)
{
    v[a][b] = true;
    dist++;
    if((a+dir[d].first==n)||(b+dir[d].second==n)||(a+dir[d].first==-1)||(b+dir[d].second==-1)||(bar[a+dir[d].first][b+dir[d].second]))
    {
        bool z = false;
        d = (d+1)%4;
        if(!((a+dir[d].first==n)||(b+dir[d].second==n)||(a+dir[d].first==-1)||(b+dir[d].second==-1)||(v[a+dir[d].first][b+dir[d].second])||(bar[a+dir[d].first][b+dir[d].second])))
        {
            z = true;
            dfs(a+dir[d].first,b+dir[d].second,d);
        }
        d = (d+2)%4;
        if(!((a+dir[d].first==n)||(b+dir[d].second==n)||(a+dir[d].first==-1)||(b+dir[d].second==-1)||(v[a+dir[d].first][b+dir[d].second])||(bar[a+dir[d].first][b+dir[d].second])))
        {
            z = true;
            dfs(a+dir[d].first,b+dir[d].second,d);
        }
        if(!z)
        {
            ans = max(ans,dist);
        }
    }
    else if(v[a+dir[d].first][b+dir[d].second])
    {
        ans = max(ans,dist);
    }
    else
    {
        dfs(a+dir[d].first,b+dir[d].second,d);
    }
    v[a][b] = false;
    dist--;
}

int main()
{
    ifstream infile("snail.in");
    ofstream outfile("snail.out");
    infile >> n >> b;
    char x;
    for(int i = 0; i<b; i++)
    {
        infile >> x >> y;
        bar[x-'A'][y-1] = true;
    }
    dfs(0,0,0);
    dfs(0,0,1);
    outfile << ans << endl;
}
