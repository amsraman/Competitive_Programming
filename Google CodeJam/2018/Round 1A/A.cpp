#include <bits/stdc++.h>

using namespace std;

int t, r, c, h, v, pre[101][101], x[101], y[101];
vector<int> xcut, ycut;
char in[100][100];

bool solve()
{
    xcut.clear(), ycut.clear();
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            pre[i+1][j+1] = pre[i][j+1]+pre[i+1][j]+(in[i][j]=='@')-pre[i][j];
    if(pre[r][c]%((h+1)*(v+1)))
        return false;
    for(int i = 1; i<=r; i++)
        x[i] = pre[i][c];
    for(int i = 1; i<=c; i++)
        y[i] = pre[r][i];
    xcut.push_back(0), ycut.push_back(0);
    for(int i = 0; i<r; i++)
        if((x[i+1]-x[xcut[xcut.size()-1]])==(pre[r][c]/(h+1)))
            xcut.push_back(i+1);
    for(int i = 0; i<c; i++)
        if((y[i+1]-y[ycut[ycut.size()-1]])==(pre[r][c]/(v+1)))
            ycut.push_back(i+1);
    if(((xcut.size()!=h+2)||(ycut.size()!=v+2))&&(pre[r][c]))
        return false;
    for(int i = 0; i<=h; i++)
        for(int j = 0; j<=v; j++)
            if((pre[xcut[i+1]][ycut[j+1]]-pre[xcut[i+1]][ycut[j]]-pre[xcut[i]][ycut[j+1]]+pre[xcut[i]][ycut[j]])!=(pre[r][c]/((h+1)*(v+1))))
                return false;
    return true;
}

int main()
{
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        cin >> r >> c >> h >> v;
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                cin >> in[i][j];
        cout << "Case #" << z+1 << ": " << (solve()?("POSSIBLE"):("IMPOSSIBLE")) << endl;
    }
}
