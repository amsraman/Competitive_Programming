#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n, m, a, b, x[25002], y[25002], xc = 1, yc = 1, ans;

int main()
{
    ifstream infile("fencedin.in");
    ofstream outfile("fencedin.out");
    infile >> a >> b >> n >> m;
    for(int i = 0; i<n; i++)
    {
        infile >> x[i];
    }
    for(int i = 0; i<m; i++)
    {
        infile >> y[i];
    }
    x[n] = a, y[m] = b;
    sort(x,x+n+2);
    sort(y,y+m+2);
    for(int i = 0; i<=n; i++)
    {
        x[i] = x[i+1]-x[i];
    }
    for(int i = 0; i<=m; i++)
    {
        y[i] = y[i+1]-y[i];
    }
    sort(x,x+n+1);
    sort(y,y+m+1);
    ans = x[0]*(m)+y[0]*(n);
    while((xc<=n)&&(yc<=m))
    {
        if(x[xc]<y[yc])
        {
            ans+=(x[xc]*(m-yc+1));
            xc++;
        }
        else
        {
            ans+=(y[yc]*(n-xc+1));
            yc++;
        }
    }
    outfile << ans << endl;
}
