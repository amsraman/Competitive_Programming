#include <fstream>
#include <iostream>
#include <map>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("hayfeast.in");
    ofstream outfile("hayfeast.out");
    int n;
    long long m;
    infile >> n >> m;
    int b[n], c2 = 0, ans = INF, z;
    long long p[n+1];
    p[0] = 0;
    map<int,int> c;
    map<int,int>::iterator x;
    for(int i = 0; i<n; i++)
    {
        infile >> z >> b[i];
        p[i+1] = z+p[i];
    }
    for(int i = 0; i<n; i++)
    {
        while(p[i]+m>p[c2])
        {
            c2++;
            if(c2==n+1)
            {
                i = n+1;
                break;
            }
            if(!c.count(b[c2-1]))
            {
                c[b[c2-1]] = 0;
            }
            c[b[c2-1]]++;
        }
        if(i!=n+1)
        {
            x = c.end();
            x--;
            ans = min(ans,x->first);
            if(c[b[i]]==1)
            {
                c.erase(b[i]);
            }
            else
            {
                c[b[i]]--;
            }
        }
    }
    outfile << ans << endl;
}
