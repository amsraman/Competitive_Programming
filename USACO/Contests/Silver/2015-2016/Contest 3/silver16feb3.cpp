#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int x, y, k, m, ans = 10000, p[101][101];
bool v[101][101] = {false};

void dfs(int a, int b, int c)
{
    if((c==k+1)||((v[a][b])&&(c>=p[a][b])))
    {
        return;
    }
    v[a][b] = true;
    p[a][b] = c;
    ans = min(ans,abs(a+b-m));
    dfs(x,b,c+1);
    dfs(a,y,c+1);
    dfs(0,b,c+1);
    dfs(a,0,c+1);
    dfs(a-min(a,y-b),b+min(a,y-b),c+1);
    dfs(a+min(b,x-a),b-min(b,x-a),c+1);
}

int main()
{
    ifstream infile("pails.in");
    ofstream outfile("pails.out");
    infile >> x >> y >> k >> m;
    dfs(0,0,0);
    outfile << ans << endl;
}
