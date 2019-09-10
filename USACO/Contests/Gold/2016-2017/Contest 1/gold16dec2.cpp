#include <fstream>
#include <iostream>
#define INF 0xfffffffff

using namespace std;

int main()
{
    ifstream infile("checklist.in");
    ofstream outfile("checklist.out");
    int h, g;
    infile >> h >> g;
    long long dp1[h+1][g+1], dp2[h+1][g+1];
    pair<int,int> ph[h], pg[g];
    for(int i = 0; i<h; i++)
    {
        infile >> ph[i].first >> ph[i].second;
    }
    for(int i = 0; i<g; i++)
    {
        infile >> pg[i].first >> pg[i].second;
    }
    for(int i = 0; i<=g; i++)
    {
        dp1[0][i] = dp2[0][i] = INF;
    }
    dp1[1][0] = dp2[1][0] = 0;
    for(int i = 1; i<=h; i++)
    {
        for(int j = 0; j<=g; j++)
        {
            if((i!=1)||(j!=0)){dp1[i][j] = dp2[i][j] = INF;}
            if((i>0)&&(j>0))
            {
                dp1[i][j] = min(dp1[i][j],dp2[i-1][j]+(ph[i-1].first-pg[j-1].first)*(ph[i-1].first-pg[j-1].first)+(ph[i-1].second-pg[j-1].second)*(ph[i-1].second-pg[j-1].second));
            }
            if((i>0)&&(j>0))
            {
                dp2[i][j] = min(dp2[i][j],dp1[i][j-1]+(ph[i-1].first-pg[j-1].first)*(ph[i-1].first-pg[j-1].first)+(ph[i-1].second-pg[j-1].second)*(ph[i-1].second-pg[j-1].second));
            }
            if(i>1)
            {
                dp1[i][j] = min(dp1[i][j],dp1[i-1][j]+(ph[i-1].first-ph[i-2].first)*(ph[i-1].first-ph[i-2].first)+(ph[i-1].second-ph[i-2].second)*(ph[i-1].second-ph[i-2].second));
            }
            if(j>1)
            {
                dp2[i][j] = min(dp2[i][j],dp2[i][j-1]+(pg[j-1].first-pg[j-2].first)*(pg[j-1].first-pg[j-2].first)+(pg[j-1].second-pg[j-2].second)*(pg[j-1].second-pg[j-2].second));
            }
        }
    }
    outfile << dp1[h][g] << endl;
}
