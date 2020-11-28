#include <fstream>
#include <iostream>

using namespace std;

int r, c;
bool v[100][100] = {false};
int in[100][100];
long s[100][100];

long solve(int a, int b)
{
    if(v[a][b])
    {
        return s[a][b];
    }
    v[a][b] = true;
    long r = 0;
    for(int i = 0; i<a; i++)
    {
        for(int j = 0; j<b; j++)
        {
            if(in[i][j]!=in[a][b])
            {
                r = r+s[i][j];
            }
        }
    }
    return r;
}

int main()
{
    int k;
    ifstream infile("hopscotch.in");
    ofstream outfile("hopscotch.out");
    infile >> r >> c >> k;
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            infile >> in[i][j];
        }
    }
    s[0][0] = 1;
    v[0][0] = true;
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            s[i][j] = solve(i,j)%1000000007;
        }
    }
    int ans = s[r-1][c-1]%1000000007;
    if(ans<0)
    {
        ans = ans+1000000007;
    }
    outfile << ans << endl;
}
