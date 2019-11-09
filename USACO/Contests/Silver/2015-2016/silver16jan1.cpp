#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int s[50000];

bool valid(int p)
{
    int c = 0, lim = s[0]+2*p;
    for(int i = 0; i<n; i++)
    {
        if(s[i]>lim)
        {
            c++;
            lim = s[i]+2*p;
            if(c==k)
            {
                return false;
            }
        }
    }
    return true;
}

int bsearch(int l, int g)
{
    if(l==g)
    {
        return l;
    }
    int mid = (l+g)/2;
    if(valid(mid))
    {
        bsearch(l,mid);
    }
    else
    {
        bsearch(mid+1,g);
    }
}

int main()
{
    ifstream infile("angry.in");
    ofstream outfile("angry.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> s[i];
    }
    sort(s,s+n);
    outfile << bsearch(1,(s[n-1]-s[0])/2);
}
