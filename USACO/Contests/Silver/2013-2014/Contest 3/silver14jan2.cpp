#include <fstream>
#include <iostream>

using namespace std;

int m, n, e[500][500], wp[500][500], wpc = 0, cwpc, xpos, ypos;
bool v[500][500] = {false};

void dfs(int a, int b, int z)
{
    v[a][b] = true;
    if(wp[a][b]==1)
    {
        cwpc++;
    }
    if((a>0)&&(!v[a-1][b])&&((max(e[a-1][b],e[a][b])-min(e[a-1][b],e[a][b])<=z)))
    {
        dfs(a-1,b,z);
    }
    if((a<m-1)&&(!v[a+1][b])&&((max(e[a+1][b],e[a][b])-min(e[a+1][b],e[a][b])<=z)))
    {
        dfs(a+1,b,z);
    }
    if((b>0)&&(!v[a][b-1])&&((max(e[a][b-1],e[a][b])-min(e[a][b-1],e[a][b])<=z)))
    {
        dfs(a,b-1,z);
    }
    if((b<n-1)&&(!v[a][b+1])&&((max(e[a][b+1],e[a][b])-min(e[a][b+1],e[a][b])<=z)))
    {
        dfs(a,b+1,z);
    }
}

int bsearch(int l, int g)
{
    if(l==g)
    {
        return g;
    }
    cwpc = 0;
    for(int i = 0; i<m; i++)
    {
        for(int j = 0; j<n; j++)
        {
            v[i][j] = false;
        }
    }
    int mid = (l+g)/2;
    dfs(xpos,ypos,mid);
    if(cwpc!=wpc)
    {
        return bsearch(mid+1,g);
    }
    else
    {
        return bsearch(l,mid);
    }
}

int main()
{
    ifstream infile("ccski.in");
    ofstream outfile("ccski.out");
    infile >> m >> n;
    for(int i = 0; i<m; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> e[i][j];
        }
    }
    for(int i = 0; i<m; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> wp[i][j];
            if(wp[i][j]==1)
            {
                xpos = i;
                ypos = j;
                wpc++;
            }
        }
    }
    outfile << bsearch(0,1000000000) << endl;
}
