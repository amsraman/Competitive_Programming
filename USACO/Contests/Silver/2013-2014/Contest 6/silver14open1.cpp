#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<pair<int,int> > num;

int bin(int l, int g, int a)
{
    int mid = (l+g)/2;
    if((l<0)||(g<0))
    {
        return num[0].second;
    }
    if(l==g)
    {
        return num[l].second;
    }
    if(num[mid].first==a)
    {
        return num[mid].second;
    }
    else if(num[mid].first<a)
    {
        return bin(l,mid-1,a);
    }
    else
    {
        return bin(mid+1,g,a);
    }
}

int main()
{
    ifstream infile("fairphoto.in");
    ofstream outfile("fairphoto.out");
    int n;
    infile >> n;
    pair<int,char> in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first >> in[i].second;
    }
    sort(in,in+n);
    pair<int,int> p[n];
    p[0] = {0,-1};
    for(int i = 0; i<n; i++)
    {
        if(in[i].second=='W')
        {
            p[i+1] = {p[i].first+1,i};
        }
        else
        {
            p[i+1] = {p[i].first-1,i};
        }
    }
    num.push_back({0,-1});
    for(int i = 1; i<n; i++)
    {
        if(p[i].first<num[num.size()-1].first)
        {
            num.push_back({p[i].first,p[i].second});
        }
    }
    int c = num.size()-1;
    int ans = 0;
    for(int i = n; i>1; i--)
    {
        if(num[c].second==p[i+1].second)
        {
            c--;
        }
        int a = bin(0,c,p[i+1].first);
        a+=(i-a)%2;
        if((i<n)&&(a<n-1))
        {
            ans = max(ans,in[i].first-in[a+1].first);
        }
    }
    outfile << ans << endl;
}
