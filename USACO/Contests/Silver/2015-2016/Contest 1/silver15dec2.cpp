#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("highcard.in");
    ofstream outfile("highcard.out");
    int n;
    infile >> n;
    int p1[n], p2[n], c[n];
    for(int i = 0; i<n; i++)
    {
        infile >> p1[i];
    }
    sort(p1,p1+n);
    int c1 = 0, c2 = 0;
    for(int i = 1; i<=2*n; i++)
    {
        if(i==p1[c1])
        {
            c1++;
        }
        else
        {
            c[c2] = i;
            c2++;
        }
    }
    c1 = 0;
    c2 = n-1;
    for(int i = n-1; i>=0; i--)
    {
        if(c[c2]>p1[i])
        {
            p2[i] = c[c2];
            c2--;
        }
        else
        {
            p2[i] = c[c1];
            c1++;
        }
    }
    int ans = 0;
    for(int i = 0; i<n; i++)
    {
        if(p2[i]>p1[i])
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
