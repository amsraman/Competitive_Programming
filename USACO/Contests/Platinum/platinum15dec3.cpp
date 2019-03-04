#include <fstream>
#include <iostream>
#define INF 0xfffffffffffffff

using namespace std;

int n, q, a, b, c, in[200000];
long long seg1[(1<<19)][2], seg2[(1<<19)][2];

void build(int a, int b, int l)
{
    if(a==b)
    {
        seg1[l][0] = seg2[l][0] = in[a];
        return;
    }
    int mid = (a+b)/2;
    build(a,mid,2*(l+1)-1);
    build(mid+1,b,2*(l+1));
    seg1[l][0] = seg1[2*(l+1)-1][0]+seg1[2*(l+1)][0];
    seg2[l][0] = min(seg2[2*(l+1)-1][0],seg2[2*(l+1)][0]);
}

long long sum(int a, int b, int s, int e, int l)
{
    if((a==s)&&(b==e))
    {
        return seg1[l][0];
    }
    int mid = (s+e)/2;
    seg1[2*(l+1)-1][0]+=(mid-s+1)*seg1[l][1];
    seg1[2*(l+1)][0]+=(e-mid)*seg1[l][1];
    seg1[2*(l+1)-1][1]+=seg1[l][1];
    seg1[2*(l+1)][1]+=seg1[l][1];
    seg1[l][1] = 0;
    if(a>mid){return sum(a,b,mid+1,e,2*(l+1));}
    else if(b<=mid){return sum(a,b,s,mid,2*(l+1)-1);}
    else{return sum(a,mid,s,mid,2*(l+1)-1)+sum(mid+1,b,mid+1,e,2*(l+1));}
}

long long minv(int a, int b, int s, int e, int l)
{
    if((a==s)&&(b==e))
    {
        return seg2[l][0];
    }
    seg2[2*(l+1)-1][0]+=seg2[l][1];
    seg2[2*(l+1)-1][1]+=seg2[l][1];
    seg2[2*(l+1)][0]+=seg2[l][1];
    seg2[2*(l+1)][1]+=seg2[l][1];
    seg2[l][1] = 0;
    int mid = (s+e)/2;
    if(a>mid){return minv(a,b,mid+1,e,2*(l+1));}
    else if(b<=mid){return minv(a,b,s,mid,2*(l+1)-1);}
    else{return min(minv(a,mid,s,mid,2*(l+1)-1),minv(mid+1,b,mid+1,e,2*(l+1)));}
}

void update(int a, int b, long long c, int s, int e, int l)
{
    if((a==s)&&(b==e))
    {
        seg1[l][0]+=(b-a+1)*c;
        seg1[l][1]+=c;
        seg2[l][0]+=c;
        seg2[l][1]+=c;
        return;
    }
    int mid = (s+e)/2;
    if(a>mid){update(a,b,c,mid+1,e,2*(l+1));}
    else if(b<=mid){update(a,b,c,s,mid,2*(l+1)-1);}
    else{update(mid+1,b,c,mid+1,e,2*(l+1));update(a,mid,c,s,mid,2*(l+1)-1);}
    seg1[l][0] = seg1[2*(l+1)-1][0]+seg1[2*(l+1)][0]+(e-s+1)*seg1[l][1];
    seg2[l][0] = min(seg2[2*(l+1)-1][0],seg2[2*(l+1)][0])+seg2[l][1];
}

int main()
{
    ifstream infile("haybales.in");
    ofstream outfile("haybales.out");
    infile >> n >> q;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int i = 0; i<(1<<19); i++){seg2[i][0] = INF;}
    build(0,n-1,0);
    char z;
    for(int i = 0; i<q; i++)
    {
        infile >> z;
        if(z=='M')
        {
            infile >> a >> b;
            outfile << minv(a-1,b-1,0,n-1,0) << endl;
        }
        if(z=='P')
        {
            infile >> a >> b >> c;
            update(a-1,b-1,c,0,n-1,0);
        }
        if(z=='S')
        {
            infile >> a >> b;
            outfile << sum(a-1,b-1,0,n-1,0) << endl;
        }
    }
}
