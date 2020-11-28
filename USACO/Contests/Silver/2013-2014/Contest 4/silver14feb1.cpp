#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int w;
vector<pair<string,int> > dict;

int bsearch(int l, int g, string s)
{
    int mid = (l+g)/2;
    if(l==g)
    {
        return l;
    }
    if(dict[mid].first>=s)
    {
        return bsearch(0,mid,s);
    }
    else
    {
        return bsearch(mid+1,g,s);
    }
}

int main()
{
    ifstream infile("auto.in");
    ofstream outfile("auto.out");
    int n, k;
    string in;
    infile >> w >> n;
    for(int i = 0; i<w; i++)
    {
        infile >> in;
        dict.push_back({in,i+1});
    }
    sort(dict.begin(),dict.end());
    for(int i = 0; i<n; i++)
    {
        infile >> k >> in;
        int p = bsearch(0,w-1,in);
        if((p+k-1>=w)||(dict[p+k-1].first.substr(0,min(dict[p+k-1].first.length(),in.length()))!=in.substr(0,min(dict[p+k-1].first.length(),in.length()))))
        {
            outfile << -1 << endl;
        }
        else
        {
            outfile << dict[p+k-1].second << endl;
        }
    }
}
