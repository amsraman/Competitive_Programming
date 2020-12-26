#include <bits/stdc++.h>
#define f first
#define s second
 
using namespace std;
 
int n, rad[100000], lo[100000], hi[100000], segmin[(1<<18)], segmax[(1<<18)], ans[100000];
pair<int,int> ind[100000];
 
int qmax(int low, int high)
{
    low+=(1<<17), high+=(1<<17);
    int ret = 0;
    while(low<=high)
    {
        if(high%2==0) ret = max(ret,segmax[high]), high--;
        if(low%2==1) ret = max(ret,segmax[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}
 
int qmin(int low, int high)
{
    low+=(1<<17), high+=(1<<17);
    int ret = 0x3f3f3f3f;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret,segmin[high]), high--;
        if(low%2==1) ret = min(ret,segmin[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}
 
void updmax(int k, int x)
{
    k+=(1<<17), segmax[k] = x;
    while(k>1)
        k/=2, segmax[k] = max(segmax[2*k],segmax[2*k+1]);
}
 
void updmin(int k, int x)
{
    k+=(1<<17), segmin[k] = x;
    while(k>1)
        k/=2, segmin[k] = min(segmin[2*k],segmin[2*k+1]);
}
 
int main()
{
    cin >> n;
    while(n!=0)
    {
        for(int i = 0; i<n; i++)
            cin >> ind[i].f >> rad[i];
        for(int i = 0; i<n; i++)
            ind[i].s = i;
        sort(ind,ind+n);
        memset(segmin,0x3f3f3f3f,sizeof(segmin));
        memset(segmax,0,sizeof(segmax));
        for(int i = 0; i<n; i++)
        {
            int lb1 = i, ub1 = n-1, lb2 = 0, ub2 = i;
            while(lb1<ub1)
            {
                int mid = (lb1+ub1+1)/2;
                if(ind[mid].f<=ind[i].f+rad[ind[i].s])
                    lb1 = mid;
                else
                    ub1 = mid-1;
            }
            while(lb2<ub2)
            {
                int mid = (lb2+ub2)/2;
                if(ind[mid].f>=ind[i].f-rad[ind[i].s])
                    ub2 = mid;
                else
                    lb2 = mid+1;
            }
            hi[i] = ub1, lo[i] = ub2;
            updmax(i,hi[i]), updmin(i,lo[i]);
        }
        for(int i = 0; i<n; i++)
        {
            bool done = false;
            while(!done)
            {
                done|=(hi[i]==qmax(lo[i],hi[i])&&lo[i]==qmin(lo[i],hi[i]));
                hi[i] = qmax(lo[i],hi[i]), lo[i] = qmin(lo[i],hi[i]);
            }
            updmax(i,hi[i]), updmin(i,lo[i]);
        }
        for(int i = 0; i<n; i++)
            ans[ind[i].s] = hi[i]-lo[i]+1;
        for(int i = 0; i<n; i++)
            cout << ans[i] << " ";
        cout << endl;
        cin >> n;
    }
}