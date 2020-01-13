/*
ID: adityasund1
TASK: buylow
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> mult[5001];

void add(int a, int b)
{
    int co = 0;
    for(int i = 0; i<min(mult[a].size(),mult[b].size()); i++)
    {
        int k = mult[a][i]+mult[b][i]+co;
        mult[a][i] = k%10;
        co = k/10;
    }
    if(mult[a].size()>=mult[b].size())
    {
        int pos = mult[b].size();
        while(co!=0)
        {
            if(pos>=mult[a].size())
            {
                mult[a].push_back(co);
                break;
            }
            int k = co+mult[a][pos];
            mult[a][pos] = k%10;
            co = k/10;
        }
    }
    else
    {
        for(int i = mult[a].size(); i<mult[b].size(); i++)
        {
            int k = co+mult[b][i];
            mult[a].push_back(k%10);
            co = k/10;
        }
        if(co!=0){mult[a].push_back(co);}
    }
}

int main()
{
    ifstream infile("buylow.in");
    ofstream outfile("buylow.out");
    int n;
    vector<pair<pair<int,int>,int> > v;
    infile >> n;
    int ar[n+1], dp[n+1], ans = 0, mult2 = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
    }
    ar[n] = 0;
    for(int i = 0; i<=n; i++)
    {
        mult[i].push_back(0);
        dp[i] = 0;
        for(int j = 0; j<i; j++)
        {
            if(ar[j]>ar[i])
            {
                dp[i] = max(dp[i],dp[j]);
            }
        }
        for(int j = 0; j<i; j++)
        {
            if((dp[i]==dp[j])&&(ar[j]>ar[i]))
            {
                v.push_back({{ar[j],dp[j]},j});
            }
        }
        v.push_back({{0x3f3f3f3f,0},0});
        sort(v.begin(),v.end());
        for(int j = v.size()-2; j>=0; j--)
        {
            if((v[j].first.first!=v[j+1].first.first)||(v[j].first.second!=v[j+1].first.second))
            {
                add(i,v[j].second);
            }
        }
        if(dp[i]==0){mult[i][0] = 1;}
        dp[i]++;
        while(v.size()!=0){v.pop_back();}
    }
    outfile << dp[n]-1 << " ";
    for(int i = mult[n].size()-1; i>=0; i--){outfile << mult[n][i];}
    outfile << endl;
}
