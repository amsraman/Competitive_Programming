/*
ID: adityasund1
LANG: C++
TASK: lamps
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int p[4];
vector<pair<int,int> > in;
vector<string> ans;

bool valid()
{
    int a;
    for(int i = 0; i<in.size(); i++)
    {
        a = 1;
        a+=p[0];
        if((p[1]==1)&&((in[i].first%2)==1)){a++;}
        if((p[2]==1)&&((in[i].first%2)==0)){a++;}
        if((p[3]==1)&&((in[i].first%3)==1)){a++;}
        if(a%2!=in[i].second)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream infile("lamps.in");
    ofstream outfile("lamps.out");
    int n, c, a;
    infile >> n >> c;
    infile >> a;
    while(a!=-1)
    {
        in.push_back({a,1});
        infile >> a;
    }
    infile >> a;
    while(a!=-1)
    {
        in.push_back({a,0});
        infile >> a;
    }
    for(int i = 0; i<16; i++)
    {
        p[0] = p[1] = p[2] = p[3] = 0;
        bool b = (i&8);
        p[0] = int(b);
        b = (i&4);
        p[1] = int(b);
        b = (i&2);
        p[2] = int(b);
        b = (i&1);
        p[3] = int(b);
        if(((p[0]+p[1]+p[2]+p[3])%2==c%2)&&((p[0]+p[1]+p[2]+p[3])<=c)&&(valid()))
        {
            string s = "";
            for(int j = 1; j<=n; j++)
            {
                a = 1;
                a+=p[0];
                if((p[1]==1)&&(j%2==1)){a++;}
                if((p[2]==1)&&(j%2==0)){a++;}
                if((p[3]==1)&&(j%3==1)){a++;}
                if(a%2==0){s+="0";}
                if(a%2==1){s+="1";}
            }
            ans.push_back(s);
        }
    }
    if(ans.size()==0)
    {
        outfile << "IMPOSSIBLE" << endl;
    }
    else
    {
        sort(ans.begin(),ans.end());
        for(int i = 0; i<ans.size(); i++)
        {
            outfile << ans[i] << endl;
        }
    }
}
