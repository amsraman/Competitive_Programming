#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("div7.in");
    ofstream outfile("div7.out");
    int n, in, t = 0, ans = 0;
    vector<int> v[7];
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in;
        t = (t+in)%7;
        v[t].push_back(i);
    }
    for(int i = 0; i<7; i++)
    {
        if(v[i].size()!=0)
        {
            ans = max(ans,v[i][v[i].size()-1]-v[i][0]);
        }
    }
    outfile << ans << endl;
}
