/*
ID: adityasund1
TASK: game1
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("game1.in");
    ofstream outfile("game1.out");
    int n;
    infile >> n;
    int ar[n], dp1[n][n], dp2[n][n];
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
        dp1[i][i] = 0;
        dp2[i][i] = ar[i];
    }
    for(int i = n-1; i>=0; i--)
    {
        for(int j = i+1; j<n; j++)
        {
            if((j-i)%2==1)
            {
                if(dp1[i+1][j]+ar[i]>dp1[i][j-1]+ar[j])
                {
                    dp1[i][j] = dp1[i+1][j]+ar[i];
                    dp2[i][j] = dp2[i+1][j];
                }
                else
                {
                    dp1[i][j] = dp1[i][j-1]+ar[j];
                    dp2[i][j] = dp2[i][j-1];
                }
            }
            else
            {
                if(dp2[i+1][j]+ar[i]>dp2[i][j-1]+ar[j])
                {
                    dp2[i][j] = dp2[i+1][j]+ar[i];
                    dp1[i][j] = dp1[i+1][j];
                }
                else
                {
                    dp2[i][j] = dp2[i][j-1]+ar[j];
                    dp1[i][j] = dp1[i][j-1];
                }
            }
        }
    }
    if(n%2==0)
    {
        outfile << dp1[0][n-1] << " " << dp2[0][n-1] << endl;
    }
    else
    {
        outfile << dp2[0][n-1] << " " << dp1[0][n-1] << endl;
    }
}
