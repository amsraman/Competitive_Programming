#include <fstream>
#include <iostream>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("trapped.in");
    ofstream outfile("trapped.out");
    int n, b;
    infile >> n >> b;
    pair<int,int> in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].second >> in[i].first;
    }
    sort(in,in+n);
    if((b<in[0].first)||(b>in[n-1].first))
    {
        outfile << -1 << endl;
        return 0;
    }
    int c1, c2;
    for(int i = 0; i<n-1; i++)
    {
        if((b>in[i].first)&&(b<in[i+1].first))
        {
            c1 = i;
            c2 = i+1;
        }
    }
    int c3 = c2, m = 0, ans = INF;
    for(int i = c1; i>=0; i--)
    {
        if(i!=c1)
        {
            m = in[i+1].second;
        }
        while((in[c3].first-in[i].first>in[c3].second)||(in[c3].first-in[i].first<=m))
        {
            c3++;
            if(c3==n)
            {
                i = -1;
                break;
            }
        }
        if(i!=-1)
        {
            ans = min(ans,max(0,in[c3].first-in[i].first-in[i].second));
        }
    }
    c3 = c1, m = 0;
    for(int i = c2; i<n; i++)
    {
        if(i!=c2)
        {
            m = in[i-1].second;
        }
        while((in[i].first-in[c3].first>in[c3].second)||(in[i].first-in[c3].first<=m))
        {
            c3--;
            if(c3==-1)
            {
                i = n;
                break;
            }
        }
        if(i!=n)
        {
            ans = min(ans,max(0,in[i].first-in[c3].first-in[i].second));
        }
    }
    if(ans==INF)
    {
        outfile << -1 << endl;
    }
    else
    {
        outfile << ans << endl;
    }
}
