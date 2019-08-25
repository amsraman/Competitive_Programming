#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, pos[100000], mp, bit[100001][2], ans = 0x3f3f3f3f;
pair<int,int> x[100000], y[100000];

int sum(int k, int s)
{
    k++;
    int ret = 0;
    while(k>0)
    {
        ret+=bit[k][s];
        k-=(k&(-k));
    }
    return ret;
}

void update(int k, int inc, int s)
{
    k++;
    while(k<=n)
    {
        bit[k][s]+=inc;
        k+=(k&(-k));
    }
}

int main()
{
    ifstream infile("balancing.in");
    ofstream outfile("balancing.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> x[i].first >> y[i].first;
        x[i].second = y[i].second = i;
    }
    sort(x,x+n);
    sort(y,y+n);
    for(int i = 0; i<n; i++)
    {
        if((i!=0)&&(y[i-1].first!=y[i].first))
        {
            mp++;
        }
        pos[y[i].second] = mp;
        update(mp,1,1);
    }
    for(int i = 0; i<n; i++)
    {
        int curx = x[i].first, low = 0, high = mp;
        while((x[i].first==curx)&&(i<n))
        {
            update(pos[x[i].second],1,0);
            update(pos[x[i].second],-1,1);
            i++;
        }
        i--;
        while(low<high-1)
        {
            int mid = (low+high)/2;
            if(max(sum(mp,0)-sum(mid,0),sum(mp,1)-sum(mid,1))==max(sum(mid,0),sum(mid,1)))
            {
                low = high = mid;
            }
            else if(max(sum(mp,0)-sum(mid,0),sum(mp,1)-sum(mid,1))>max(sum(mid,0),sum(mid,1)))
            {
                low = mid;
            }
            else
            {
                high = mid;
            }
        }
        ans = min(ans,min(max(max(sum(mp,0)-sum(low,0),sum(low,0)),max(sum(mp,1)-sum(low,1),sum(low,1))),max(max(sum(mp,0)-sum(high,0),sum(high,0)),max(sum(mp,1)-sum(high,1),sum(high,1)))));
    }
    outfile << ans << endl;
}
