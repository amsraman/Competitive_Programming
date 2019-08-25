#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
typedef long long ll;

using namespace std;

ll n, in[5], ans;
vector<int> subs;
map<pair<pair<ll,ll>,int>,int> m;

void gen(int a)
{
    if(a==5)
    {
        ll x = 0, y = 0;
        for(int i = 0; i<min(int(subs.size()),2); i++)
        {
            x*=1000001;
            x+=subs[i];
        }
        for(int i = 2; i<subs.size(); i++)
        {
            y*=1000001;
            y+=subs[i];
        }
        if(!m.count({{x,y},subs.size()}))
        {
            m[{{x,y},subs.size()}] = 1;
        }
        else
        {
            m[{{x,y},subs.size()}]++;
        }
        return;
    }
    subs.push_back(in[a]);
    gen(a+1);
    subs.pop_back();
    gen(a+1);
}

int main()
{
    ifstream infile("cowpatibility.in");
    ofstream outfile("cowpatibility.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<5; j++)
        {
            infile >> in[j];
        }
        sort(in,in+5);
        gen(0);
    }
    map<pair<pair<ll,ll>,int>,int>::iterator it = m.begin();
    it++;
    while(it!=m.end())
    {
        ll x = it->first.second, y = it->second;
        ans+=((2*(x%2)-1)*(y)*(y-1)/2);
        it++;
    }
    outfile << (n*(n-1)/2)-ans << endl;
}
