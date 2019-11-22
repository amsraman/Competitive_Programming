#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int s[100000];

int bsearch(int l, int g, int a)
{
    int mid = (l+g)/2;
    if(l>g)
    {
        return g;
    }
    if(s[mid]>a)
    {
        bsearch(l,mid-1,a);
    }
    else if(s[mid]<a)
    {
        bsearch(mid+1,g,a);
    }
    else
    {
        return mid;
    }
}

int main()
{
    ifstream infile("haybales.in");
    ofstream outfile("haybales.out");
    int q;
    infile >> n >> q;
    for(int i = 0; i<n; i++)
    {
        infile >> s[i];
    }
    sort(s,s+n);
    int a, b;
    for(int i = 0; i<q; i++)
    {
        infile >> a >> b;
        outfile << bsearch(0,n-1,b)-bsearch(0,n-1,a-1) << endl;
    }
}

