#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int c, n, t1, t2, i, ans = 0;
    ifstream infile("helpcross.in");
    ofstream outfile("helpcross.out");
    infile >> c >> n;
    vector<int> ch;
    vector< pair<int,int> > co;
    for(int i = 0; i<c; i++)
    {
        infile >> t1;
        ch.push_back(t1);
    }
    for(int i = 0; i<n; i++)
    {
        infile >> t1 >> t2;
        co.push_back({t2,t1});
    }
    sort(ch.begin(),ch.end());
    sort(co.begin(),co.end());
    t1 = 0, t2 = 0;
    while((co.size()>0)&&(ch.size()>0))
    {
        i = 0;
        while(ch[0]>co[t2].first)
        {
            co.erase(co.begin());
        }
        while(ch[0]<co[i].second)
        {
            i++;
            if(i==co.size())
            {
                break;
            }
        }
        if(i==co.size())
        {
            ch.erase(ch.begin());
        }
        else
        {
            ans++;
            ch.erase(ch.begin());
            co.erase(co.begin()+i);
        }
    }
    outfile << ans << endl;
}
