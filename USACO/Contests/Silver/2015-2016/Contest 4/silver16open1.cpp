#include <fstream>
#include <iostream>
#include <set>
#define INF 0x3f3f3f3f

using namespace std;

int n, ans = 40000*40000;
set<pair<int,int> > sx, sy;

void dfs(int a)
{
    if(a==3)
    {
        ans = min(ans,((*(--sx.end())).first-(*(sx.begin())).first)*((*(--sy.end())).first-(*(sy.begin())).first));
        return;
    }
    int x = (*(sx.begin())).first, y = (*(sx.begin())).second;
    sx.erase({x,y});
    sy.erase({y,x});
    dfs(a+1);
    sx.insert({x,y});
    sy.insert({y,x});

    x = (*(sy.begin())).first, y = (*(sy.begin())).second;
    sx.erase({y,x});
    sy.erase({x,y});
    dfs(a+1);
    sx.insert({y,x});
    sy.insert({x,y});

    x = (*(--sx.end())).first, y = (*(--sx.end())).second;
    sx.erase({x,y});
    sy.erase({y,x});
    dfs(a+1);
    sx.insert({x,y});
    sy.insert({y,x});

    x = (*(--sy.end())).first, y = (*(--sy.end())).second;
    sx.erase({y,x});
    sy.erase({x,y});
    dfs(a+1);
    sx.insert({y,x});
    sy.insert({x,y});
}

int main()
{
    ifstream infile("reduce.in");
    ofstream outfile("reduce.out");
    infile >> n;
    int a, b;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        sx.insert({a,b});
        sy.insert({b,a});
    }
    dfs(0);
    outfile << ans << endl;
}
