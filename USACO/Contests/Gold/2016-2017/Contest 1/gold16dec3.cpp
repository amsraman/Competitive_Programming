#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

pair<int,int> xlist[100000], ylist[100000];

int bsx(int l, int g, int k)
{
    int mid = (l+g)/2;
    if(l>=g){return g;}
    if(xlist[mid].first>=k){return bsx(l,mid,k);}
    else{return bsx(mid+1,g,k);}
}

int bsy(int l, int g, int k)
{
    int mid = (l+g)/2;
    if(l>=g){return g;}
    if(ylist[mid].first>=k){return bsy(l,mid,k);}
    else{return bsy(mid+1,g,k);}
}

int main()
{
    ifstream infile("lasers.in");
    ofstream outfile("lasers.out");
    int n, x, y, origx, origy, finx, finy;
    map<pair<int,int>,int> d;
    infile >> n >> origx >> origy >> finx >> finy;
    for(int i = 0; i<n; i++)
    {
        infile >> x >> y;
        xlist[i] = {x,y};
        ylist[i] = {y,x};
    }
    sort(xlist,xlist+n);
    sort(ylist,ylist+n);
    queue<pair<int,int> > q;
    q.push({0,origy});
    q.push({1,origx});
    d[{0,origx}] = d[{1,origy}] = 0;
    while(!q.empty())
    {
        int a = q.front().first, b = q.front().second;
        q.pop();
        if(((a==1)&&(b==finx))||((a==0)&&(b==finy)))
        {
            outfile << d[{a,b}] << endl;
            return 0;
        }
        if(a==1)
        {
            int k = bsx(0,n-1,b);
            while(xlist[k].first==b)
            {
                if(!d.count({0,xlist[k].second}))
                {
                    d[{0,xlist[k].second}] = d[{1,b}]+1;
                    q.push({0,xlist[k].second});
                }
                k++;
            }
        }
        if(a==0)
        {
            int k = bsy(0,n-1,b);
            while(ylist[k].first==b)
            {
                if(!d.count({1,ylist[k].second}))
                {
                    d[{1,ylist[k].second}] = d[{0,b}]+1;
                    q.push({1,ylist[k].second});
                }
                k++;
            }
        }
    }
    outfile << -1 << endl;
    return 0;
}
