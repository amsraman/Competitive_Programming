/*
ID: adityasund1
TASK: tour
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n, v, dp[100][100];
vector<int> g[100];
map<string,int> m;

int main()
{
    ifstream infile("tour.in");
    ofstream outfile("tour.out");
    infile >> n >> v;
    string s1, s2;
    for(int i = 0; i<n; i++)
    {
        infile >> s1;
        m[s1] = i;
        for(int j = 0; j<n; j++)
        {
            dp[i][j] = -0x3f3f3f3f;
        }
    }
    for(int i = 0; i<v; i++)
    {
        infile >> s1 >> s2;
        g[min(m[s1],m[s2])].push_back(max(m[s1],m[s2]));
        g[max(m[s1],m[s2])].push_back(min(m[s1],m[s2]));
    }
    dp[0][0] = 1;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            for(int k = 0; k<g[i].size(); k++)
            {
                if((g[i][k]>max(i,j))||((g[i][k]==j)&&(j==n-1)))
                {
                    dp[g[i][k]][j] = max(dp[g[i][k]][j],dp[i][j]+1);
                }
            }
            for(int k = 0; k<g[j].size(); k++)
            {
                if((g[j][k]>max(i,j))||((g[j][k]==i)&&(i==n-1)))
                {
                    dp[i][g[j][k]] = max(dp[i][g[j][k]],dp[i][j]+1);
                }
            }
        }
    }
    outfile << max(dp[n-1][n-1]-1,1) << endl;
}
