#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int n, q, dist[(1<<18)-1], adv[(1<<18)-1], loc[100000], qa, qb, m;
pair<int,int> p[100000];

void construct(int l, int a, int b)
{
    if(a==b)
    {
        dist[l-1] = abs(p[a+1].first-p[a].first)+abs(p[a+1].second-p[a].second);
        loc[a] = l;
        if(a!=n-2)
        {
            adv[l-1] = abs(p[a+1].first-p[a].first)+abs(p[a+1].second-p[a].second)+abs(p[a+2].first-p[a+1].first)+abs(p[a+2].second-p[a+1].second)-abs(p[a+2].first-p[a].first)-abs(p[a+2].second-p[a].second);
        }
        return;
    }
    construct(2*l,a,(a+b)/2);
    construct(2*l+1,1+(a+b)/2,b);
    dist[l-1] = dist[2*l-1]+dist[2*l];
    adv[l-1] = max(adv[2*l-1],adv[2*l]);
}

int qsum(int rt, int a, int b, int l, int g)
{
    if((a==l)&&(b==g)){return dist[rt-1];}
    int mid = (l+g)/2;
    if(b<=mid){return qsum(2*rt,a,b,l,mid);}
    else if(a>mid){return qsum(2*rt+1,a,b,mid+1,g);}
    else{return qsum(2*rt,a,mid,l,mid)+qsum(2*rt+1,mid+1,b,mid+1,g);}
}

int qmax(int rt, int a, int b, int l, int g)
{
    if(l>g){return 0;}
    if((a==l)&&(b==g)){return adv[rt-1];}
    int mid = (l+g)/2;
    if(b<=mid){return qmax(2*rt,a,b,l,mid);}
    else if(a>mid){return qmax(2*rt+1,a,b,mid+1,g);}
    else{return max(qmax(2*rt,a,mid,l,mid),qmax(2*rt+1,mid+1,b,mid+1,g));}
}

void udist(int l, int k)
{
    int pos = loc[l];
    while(pos!=0)
    {
        dist[pos-1]+=k;
        pos/=2;
    }
}

void uadv(int l, int k)
{
    int pos = loc[l];
    adv[pos-1] = k;
    while(pos!=1)
    {
        pos/=2;
        adv[pos-1] = max(adv[2*pos-1],adv[2*pos]);
    }
}

int main()
{
    ifstream infile("marathon.in");
    ofstream outfile("marathon.out");
    infile >> n >> q;
    char z;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    construct(1,0,n-2);
    for(int i = 0; i<q; i++)
    {
        infile >> z;
        if(z=='Q')
        {
            infile >> qa >> qb;
            outfile << qsum(1,qa-1,qb-2,0,n-2)-qmax(1,qa-1,qb-3,0,n-2) << endl;
        }
        else
        {
            infile >> m >> qa >> qb;
            m--;
            if(m<n-1){udist(m,abs(qa-p[m+1].first)+abs(qb-p[m+1].second)-abs(p[m+1].first-p[m].first)-abs(p[m+1].second-p[m].second));}
            if(m>0){udist(m-1,abs(qa-p[m-1].first)+abs(qb-p[m-1].second)-abs(p[m-1].first-p[m].first)-abs(p[m-1].second-p[m].second));}
            if(m<n-2){uadv(m,abs(p[m+2].first-p[m+1].first)+abs(p[m+2].second-p[m+1].second)+abs(p[m+1].first-qa)+abs(p[m+1].second-qb)-abs(p[m+2].first-qa)-abs(p[m+2].second-qb));}
            if(m>1){uadv(m-2,abs(p[m-2].first-p[m-1].first)+abs(p[m-2].second-p[m-1].second)+abs(p[m-1].first-qa)+abs(p[m-1].second-qb)-abs(p[m-2].first-qa)-abs(p[m-2].second-qb));}
            if((m>0)&&(m<n-1)){uadv(m-1,abs(p[m+1].first-qa)+abs(p[m+1].second-qb)+abs(qa-p[m-1].first)+abs(qb-p[m-1].second)-abs(p[m+1].first-p[m-1].first)-abs(p[m+1].second-p[m-1].second));}
            p[m] = {qa,qb};
        }
    }
}
