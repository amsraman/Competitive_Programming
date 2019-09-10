#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, s[100000], bit[100001] = {0};

int bsearch(int a, int b, int k)
{
    int mid = (a+b)/2;
    if(s[mid]==k)
    {
        return mid;
    }
    if(s[mid]<k)
    {
        return bsearch(mid+1,b,k);
    }
    else
    {
        return bsearch(a,mid,k);
    }
}

int sum(int a)
{
    a++;
    int ret = 0;
    while(a>0)
    {
        int k = a&(-a);
        ret+=bit[a];
        a-=k;
    }
    return ret;
}

void update(int a, int b)
{
    a++;
    while(a<=n)
    {
        int k = a&(-a);
        bit[a]+=b;
        a+=k;
    }
}

int main()
{
    ifstream infile("bphoto.in");
    ofstream outfile("bphoto.out");
    infile >> n;
    pair<int,int> ar[n];
    int l[n], r[n], ans = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i].first;
        s[i] = ar[i].first;
    }
    sort(s,s+n);
    for(int i = 0; i<n; i++)
    {
        ar[i].second = bsearch(0,n-1,ar[i].first);
    }
    for(int i = 0; i<n; i++)
    {
        l[i] = sum(n-1)-sum(ar[i].second);
        update(ar[i].second,1);
    }
    for(int i = 0; i<=n; i++)
    {
        bit[i] = 0;
    }
    for(int i = n-1; i>=0; i--)
    {
        r[i] = sum(n-1) - sum(ar[i].second);
        update(ar[i].second,1);
        if(max(r[i],l[i])>2*min(r[i],l[i]))
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
