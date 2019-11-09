/*
ID: adityasund1
TASK: money
LANG: C++
*/
#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int v, c[25];
long long dp[10001][25];
bool vi[10001][25];

long long solve(int a, int b)
{
    if(a<0)
    {
        return 0;
    }
    if((a==0)&&(b==0))
    {
        return 1;
    }
    if(vi[a][b])
    {
        return dp[a][b];
    }
    long long ret = 0;
    for(int i = 0; i<=b; i++)
    {
        ret+=solve(a-c[b],i);
    }
    return ret;
}

int main()
{
    ifstream infile("money.in");
    ofstream outfile("money.out");
    int n;
    infile >> v >> n;
    for(int i = 0; i<v; i++)
    {
        infile >> c[i];
    }
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<v; j++)
        {
            dp[i][j] = solve(i,j);
            vi[i][j] = true;
        }
    }
    long long ans = 0;
    for(int i = 0; i<v; i++)
    {
        ans+=dp[n][i];
    }
    outfile << ans << endl;
}
