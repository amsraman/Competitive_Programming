#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
int n;

int bs(int s[], int l, int g, int a)
{
    int mid = (l+g)/2;
    if(l==g)
    {
        return l;
    }
    if(a==s[n-1])
    {
        return n;
    }
    if(a>=s[mid])
    {
        return bs(s,mid+1,g,a);
    }
    if(a<s[mid])
    {
        return bs(s,l,mid,a);
    }
}


int main()
{
    ifstream infile("sort.in");
    ofstream outfile("sort.out");
    infile >> n;
    int a[n], s[n], k[n];
    for(int i = 0; i<n; i++)
    {
        infile >> a[i];
        s[i] = a[i];
    }
    sort(s,s+n);
    for(int i = 0; i<n; i++)
    {
        k[i] = bs(s,0,n-1,a[i])-1;
    }
    int ans = 0;
    for(int i = 0; i<n; i++)
    {
        ans = max(ans,i-k[i]);
    }
    outfile << ans+1 << endl;
}
