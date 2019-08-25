/*
ID: adityasund1
TASK: picture
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, a, b, c, d, cur[20001], ans;
pair<int,int> x[5000], y[5000];
vector<pair<int,pair<bool,int> > > sw1, sw2;

int main()
{
    ifstream infile("picture.in");
    ofstream outfile("picture.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> x[i].first >> y[i].first >> x[i].second >> y[i].second;
        sw1.push_back(make_pair(y[i].first,make_pair(1,i)));
        sw1.push_back(make_pair(y[i].second,make_pair(0,i)));
        sw2.push_back(make_pair(x[i].first,make_pair(1,i)));
        sw2.push_back(make_pair(x[i].second,make_pair(0,i)));
    }
    sort(sw1.begin(),sw1.end());
    sort(sw2.begin(),sw2.end());
    for(int i = 0; i<sw1.size(); i++)
    {
        if(sw1[i].second.first)
        {
            cur[x[sw1[i].second.second].first+10000]++;
            cur[x[sw1[i].second.second].second+10000]--;
        }
        else
        {
            cur[x[sw1[i].second.second].first+10000]--;
            cur[x[sw1[i].second.second].second+10000]++;
        }
        if((i<sw1.size()-1)&&(sw1[i].first!=sw1[i+1].first))
        {
            int curp = 0, tot = 0;
            for(int j = 0; j<20001; j++)
            {
                if((curp==0)&&(cur[j]>0)) tot++;
                if((curp!=0)&&(curp+cur[j]==0)) tot++;
                curp+=cur[j];
            }
            ans+=(tot*(sw1[i+1].first-sw1[i].first));
        }
    }
    for(int i = 0; i<20001; i++) cur[i] = 0;
    for(int i = 0; i<sw2.size(); i++)
    {
        if(sw2[i].second.first)
        {
            cur[y[sw2[i].second.second].first+10000]++;
            cur[y[sw2[i].second.second].second+10000]--;
        }
        else
        {
            cur[y[sw2[i].second.second].first+10000]--;
            cur[y[sw2[i].second.second].second+10000]++;
        }
        if((i<sw2.size()-1)&&(sw2[i].first!=sw2[i+1].first))
        {
            int curp = 0, tot = 0;
            for(int j = 0; j<20001; j++)
            {
                if((curp==0)&&(cur[j]>0)) tot++;
                if((curp!=0)&&(curp+cur[j]==0)) tot++;
                curp+=cur[j];
            }
            ans+=(tot*(sw2[i+1].first-sw2[i].first));
        }
    }
    outfile << ans << endl;
}
