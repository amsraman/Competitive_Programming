#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, c, in[100000];

bool valid(int a)
{
    int s = in[0], c1 = 1, c2 = 0;
    for(int i = 1; i<n; i++)
    {
        if(in[i]<=s+a)
        {
            c1++;
        }
        else
        {
            s = in[i];
            c2++;
            c1 = 1;
        }
        if((c1==c)&&(i<n-1))
        {
            c2++;
            c1 = 0;
            if(i<n)
            {
                s = in[i+1];
            }
        }
    }
    c2++;
    return (c2<=m);
}

int bsearch(int l, int g)
{
    if(l>=g)
    {
        return g;
    }
    int mid = (l+g)/2;
    if(valid(mid))
    {
        return bsearch(l,mid);
    }
    else
    {
        return bsearch(mid+1,g);
    }
}

int main()
{
    ifstream infile("convention.in");
    ofstream outfile("convention.out");
    infile >> n >> m >> c;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    sort(in,in+n);
    outfile << bsearch(0,1000000000) << endl;
}
