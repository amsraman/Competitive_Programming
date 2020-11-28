#include <fstream>
#include <iostream>

using namespace std;

int n, m, q, ar[100000], ar2[100000], trans[100000], trans2[100000];

int main()
{
    ifstream infile("shuffle.in");
    ofstream outfile("shuffle.out");
    infile >> n >> m >> q;
    int qi;
    for(int i = 0; i<m; i++)
    {
        infile >> trans[i];
        trans[i] = (trans[i]-2+n)%n;
        ar[i] = i+1;
    }
    for(int i = m; i<n; i++)
    {
        trans[i] = i-1;
        ar[i] = i+1;
    }
    int co = 0;
    while((1<<co)<=(n-m+1))
    {
        if((1<<co)&(n-m+1))
        {
            for(int i = 0; i<n; i++)
            {
                ar2[trans[i]] = ar[i];
            }
            for(int i = 0; i<n; i++)
            {
                ar[i] = ar2[i];
            }
        }
        co++;
        for(int i = 0; i<n; i++)
        {
            trans2[i] = trans[trans[i]];
        }
        for(int i = 0; i<n; i++)
        {
            trans[i] = trans2[i];
        }
    }
    for(int i = 0; i<n; i++)
    {
        ar2[(i+n-m+1)%n] = ar[i];
    }
    for(int i = 0; i<q; i++)
    {
        infile >> qi;
        outfile << ar2[n-qi] << endl;
    }
}
