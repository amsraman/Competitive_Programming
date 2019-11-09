#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int a, b, m, n, in[2002], in1, in2, link[4012009], siz[4012009];
long long ans;
pair<int,int> h[2001], v[2001];

int f(int a)
{
    while(a!=link[a]){a = link[a];}
    return a;
}

void unite(int a, int b)
{
    a = f(a);
    b = f(b);
    if(siz[a]<siz[b])
    {
        int t = b;
        b = a;
        a = t;
    }
    link[b] = a;
    siz[a]+=siz[b];
}

int main()
{
    ifstream infile("fencedin.in");
    ofstream outfile("fencedin.out");
    for(int i = 0; i<4012009; i++)
    {
        link[i] = i;
        siz[i] = 1;
    }
    int edge = 0;
    infile >> a >> b >> n >> m;
    for(int i = 0; i<n; i++){infile >> in[i+1];}
    in[n+1] = a;
    sort(in,in+n+2);
    for(int i = 1; i<=n+1; i++){h[i-1] = {in[i]-in[i-1],i-1};}
    for(int i = 0; i<m; i++){infile >> in[i+1];}
    in[m+1] = b;
    sort(in,in+m+2);
    for(int i = 1; i<=m+1; i++){v[i-1] = {in[i]-in[i-1],i-1};}
    sort(h,h+n+1);
    sort(v,v+m+1);
    while(siz[f(0)]!=(n+1)*(m+1))
    {
        if(((in1<=n)&&(in2<=m)&&(h[in1].first<v[in2].first))||(in2>m))
        {
            for(int i = 0; i<m; i++)
            {
                if(f(i*(n+2)+h[in1].second)!=f((i+1)*(n+2)+h[in1].second))
                {
                    unite((i*(n+2)+h[in1].second),((i+1)*(n+2)+h[in1].second));
                    ans+=h[in1].first;
                    edge++;
                }
            }
            in1++;
        }
        else
        {
            for(int i = 0; i<n; i++)
            {
                if(f(v[in2].second*(n+2)+i)!=f(v[in2].second*(n+2)+i+1))
                {
                    unite((v[in2].second*(n+2)+i),(v[in2].second*(n+2)+i+1));
                    ans+=v[in2].first;
                    edge++;
                }
            }
            in2++;
        }
    }
    outfile << ans << endl;
}
