#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, pu[300][300], ans[300];
pair<long long,long long> p[300];

int main()
{
    ifstream infile("triangles.in");
    ofstream outfile("triangles.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    sort(p,p+n);
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            for(int k = 0; k<n; k++)
            {
                if((k!=i)&&(k!=j)&&(p[k].first>=p[i].first)&&(p[j].first>p[k].first)&&((p[k].second-p[i].second)*(p[j].first-p[k].first)-(p[k].first-p[i].first)*(p[j].second-p[k].second)<0))
                {
                    pu[i][j]++;
                }
            }
        }
    }
    int ang = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            for(int k = j+1; k<n; k++)
            {
                if((p[j].second-p[i].second)*(p[k].first-p[j].first)-(p[j].first-p[i].first)*(p[k].second-p[j].second)>0)
                {
                    int cnt = pu[i][j]+pu[j][k]-pu[i][k];
                    if(p[i].first==p[j].first)
                    {
                        cnt--;
                    }
                    ans[cnt]++;
                }
                else
                {
                    int cnt = pu[i][k]-pu[i][j]-pu[j][k];
                    if(p[j].first!=p[k].first)
                    {
                        cnt--;
                    }
                    ans[cnt]++;
                }
            }
        }
    }
    for(int i = 0; i<n-2; i++)
    {
        outfile << ans[i] << endl;
    }
}
