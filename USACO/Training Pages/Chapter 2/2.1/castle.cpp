/*
ID: adityasund1
LANG: C++
TASK: castle
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int m, n, p[50][50], r[50][50];
bool v[50][50] = {false};

void dfs(int a, int b, int &c, int d)
{
    if(v[a][b])
    {
        return;
    }
    v[a][b] = true;
    r[a][b] = d;
    c++;
    if(!(p[a][b]&1))
    {
        dfs(a,b-1,c,d);
    }
    if(!(p[a][b]&2))
    {
        dfs(a-1,b,c,d);
    }
    if(!(p[a][b]&4))
    {
        dfs(a,b+1,c,d);
    }
    if(!(p[a][b]&8))
    {
        dfs(a+1,b,c,d);
    }
}

int main()
{
    ifstream infile("castle.in");
    ofstream outfile("castle.out");
    infile >> m >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            infile >> p[i][j];
        }
    }
    int rcount = 0, rn = 0, rmax = 0;
    vector<int> rc;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            if(!(v[i][j]))
            {
                rcount++;
                rn = 0;
                dfs(i,j,rn,rcount-1);
                rc.push_back(rn);
                rmax = max(rmax,rn);
            }
        }
    }
    int rmax2 = 0, loc[2];
    char w;
    for(int i = 0; i<m; i++)
    {
        for(int j = n-1; j>=0; j--)
        {
            if(((p[j][i]&2))&&(j>0))
            {
                if((rc[r[j][i]]+rc[r[j-1][i]]>rmax2)&&(r[j][i]!=r[j-1][i]))
                {
                    loc[0] = j;
                    loc[1] = i;
                    rmax2 = rc[r[j][i]]+rc[r[j-1][i]];
                    w = 'N';
                }
            }
            if(((p[j][i]&4))&&(i<m-1))
            {
                if((rc[r[j][i]]+rc[r[j][i+1]]>rmax2)&&(r[j][i]!=r[j][i+1]))
                {
                    loc[0] = j;
                    loc[1] = i;
                    rmax2 = rc[r[j][i]]+rc[r[j][i+1]];
                    w = 'E';
                }
            }
        }
    }
    outfile << rcount << endl << rmax << endl << rmax2 << endl << loc[0]+1 << " " << loc[1]+1 << " " << w << endl;
}
