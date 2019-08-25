#include <iostream>
#include <fstream>
#define MOD 1000000007

using namespace std;

int t, n, dp[1001][3];
char ch;
bool blocked[1001][3];

int main()
{
    ifstream fin("let_it_flow.txt");
    ofstream fout("out.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n;
        for(int i = 1; i<=n; i++)
        {
            for(int j = 0; j<3; j++)
            {
                blocked[i][j] = false;
            }
        }
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<n; j++)
            {
                fin >> ch;
                if(ch=='#') blocked[j+1][i] = true;
            }
        }
        dp[0][0] = 1;
        for(int i = 1; i<=n; i++)
        {
            dp[i][0] = dp[i][2] = dp[i-1][1]*(!blocked[i][1]);
            dp[i][1] = (dp[i-1][0]*(!blocked[i][0])+dp[i-1][2]*(!blocked[i][2]))%MOD;
            dp[i][0]*=(!blocked[i][0]), dp[i][1]*=(!blocked[i][1]), dp[i][2]*=(!blocked[i][2]);
        }
        fout << "Case #" << z+1 << ": " << dp[n][2] << endl;
    }
}
