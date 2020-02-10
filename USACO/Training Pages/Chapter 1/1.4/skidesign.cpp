/*
ID: adisund1
LANG: C++
TASK: skidesign
*/
#include <iostream>
#include <fstream>

using namespace std;

int cost(int a[], int n, int b)
{
    int ret = 0;
    int up = b+17;
    for(int i = 0; i<n; i++)
    {
        if(a[i]<b)
        {
            ret = ret+(a[i]-b)*(a[i]-b);
        }
        else if(a[i]>up)
        {
            ret = ret+(a[i]-up)*(a[i]-up);
        }
    }
    return ret;
}

int main()
{
    int n;
    ifstream infile("skidesign.in");
    ofstream outfile("skidesign.out");
    infile >> n;
    int orig[n], mod[n];
    int ma = 0, mi = 100;
    for(int i = 0; i<n; i++)
    {
        infile >> orig[i];
        mod[i] = orig[i];
        ma = max(ma,orig[i]);
        mi = min(mi,orig[i]);
    }
    int ans = mi;
    for(int i = mi; i<ma-17; i++)
    {
        if(cost(orig,n,i)<cost(orig,n,ans))
        {
            ans = i;
        }
    }
    outfile << cost(orig,n,ans) << endl;
}
