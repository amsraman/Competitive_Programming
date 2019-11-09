#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

int n, in[50000], l[50000], r[50000];
double ans = INF;

int main()
{
    ifstream infile("angry.in");
    ofstream outfile("angry.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    int c1 = 0;
    sort(in,in+n);
    for(int i = 1; i<n; i++)
    {
        l[i] = INF;
        while((l[c1]+1<=in[i]-in[c1])&&(c1<i))
        {
            l[i] = in[i]-in[c1];
            c1++;
        }
        if(c1!=i)
        {
            l[i] = min(l[i],l[c1]+1);
        }
        c1--;
    }
    c1 = n-1;
    for(int i = n-2; i>=0; i--)
    {
        r[i] = INF;
        while((r[c1]+1<=in[c1]-in[i])&&(c1>i))
        {
            r[i] = in[c1]-in[i];
            c1--;
        }
        if(c1!=i)
        {
            r[i] = min(r[i],r[c1]+1);
        }
        c1++;
    }
    c1 = 0;
    for(int i = 0; i<n; i++)
    {
        while((2*(r[c1]+1)>=in[c1]-in[i])&&(c1<n))
        {
            ans = min(ans,double(max(l[i]+1,r[c1]+1)));
            c1++;
        }
        if(c1!=n)
        {
            ans = min(ans,max(double(l[i]+1),double(in[c1]-in[i])/2));
        }
        c1--;
    }
    outfile << fixed << setprecision(1) << ans << endl;
}
