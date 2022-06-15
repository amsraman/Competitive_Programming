#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

int nu, nm, nl, uh[50000], mh[50000], lh[50000];
ll ans;
cd ucnt[(1<<17)], lcnt[(1<<17)];

void fft(cd ar[], int n, bool invert)
{
    if(n==1)
        return;
    cd ar0[n/2], ar1[n/2];
    for(int i = 0; 2*i<n; i++)
        ar0[i] = ar[2*i], ar1[i] = ar[2*i+1];
    fft(ar0,n/2,invert);
    fft(ar1,n/2,invert);
    cd w(1), wn(cos(2*PI*(invert?-1:1)/n),sin(2*PI*(invert?-1:1)/n));
    for(int i = 0; i<n/2; i++)
    {
        ar[i] = ar0[i]+w*ar1[i];
        ar[i+n/2] = ar0[i]-w*ar1[i];
        w*=wn;
    }
}

int main()
{
    cin >> nu;
    for(int i = 0; i<nu; i++)
    {
        cin >> uh[i];
        ucnt[uh[i]+30000] = 1;
    }
    cin >> nm;
    for(int i = 0; i<nm; i++)
        cin >> mh[i];
    cin >> nl;
    for(int i = 0; i<nl; i++)
    {
        cin >> lh[i];
        lcnt[lh[i]+30000] = 1;
    }
    fft(ucnt,(1<<17),false);
    fft(lcnt,(1<<17),false);
    for(int i = 0; i<(1<<17); i++)
        ucnt[i]*=lcnt[i];
    fft(ucnt,(1<<17),true);
    for(int i = 0; i<nm; i++)
        ans+=round(ucnt[2*mh[i]+60000].real()/(1<<17));
    cout << ans << endl;
}