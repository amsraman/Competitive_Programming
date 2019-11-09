/*
ID: adityasund1
TASK: shopping
LANG: C++
*/
#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int s, b, deal[999][99] = {0}, id[5], fin[5] = {0}, proff[99], normp[5], dp[6][6][6][6][6];

int main()
{
    ifstream infile("shopping.in");
    ofstream outfile("shopping.out");
    infile >> s;
    int n1, c, p, k1;
    for(int i = 0; i<s; i++)
    {
        infile >> n1;
        for(int j = 0; j<n1; j++)
        {
            infile >> c >> k1;
            deal[c-1][i] = k1;
        }
        infile >> p;
        proff[i] = p;
    }
    infile >> b;
    for(int i = 0; i<b; i++)
    {
        infile >> c >> k1 >> p;
        id[i] = c-1;
        fin[i] = k1;
        normp[i] = p;
    }
    for(int i = 0; i<=fin[0]; i++)
    {
        for(int j = 0; j<=fin[1]; j++)
        {
            for(int k = 0; k<=fin[2]; k++)
            {
                for(int l = 0; l<=fin[3]; l++)
                {
                    for(int m = 0; m<=fin[4]; m++)
                    {
                        int z[5] = {i,j,k,l,m};
                        dp[i][j][k][l][m] = INF;
                        dp[0][0][0][0][0] = 0;
                        for(int n = 0; n<b; n++)
                        {
                            if(z[n]>0)
                            {
                                z[n]--;
                                dp[i][j][k][l][m] = min(dp[i][j][k][l][m],dp[z[0]][z[1]][z[2]][z[3]][z[4]]+normp[n]);
                                z[n]++;
                            }
                        }
                        for(int n = 0; n<s; n++)
                        {
                            bool x = true;
                            for(int o = 0; o<b; o++)
                            {
                                if(z[o]<deal[id[o]][n])
                                {
                                    x = false;
                                }
                            }
                            if(x)
                            {
                                for(int o = 0; o<b; o++)
                                {
                                    z[o]-=deal[id[o]][n];
                                }
                                dp[i][j][k][l][m] = min(dp[i][j][k][l][m],dp[z[0]][z[1]][z[2]][z[3]][z[4]]+proff[n]);
                                for(int o = 0; o<b; o++)
                                {
                                    z[o]+=deal[id[o]][n];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    outfile << dp[fin[0]][fin[1]][fin[2]][fin[3]][fin[4]] << endl;
}
