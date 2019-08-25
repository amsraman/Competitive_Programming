#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int n, in[50000], pre[50000], suf[50000], cur, ans;
set<int> s1, s2;
bool v[100001];

int main()
{
    ifstream infile("cardgame.in");
    ofstream outfile("cardgame.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        v[in[i]] = true;
    }
    for(int i = 1; i<=2*n; i++)
    {
        if(!v[i])
        {
            s1.insert(i);
            s2.insert(i);
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(in[i]>(*(--s1.end())))
        {
            s1.erase(s1.begin());
            pre[i] = cur;
        }
        else
        {
            s1.erase(s1.lower_bound(in[i]));
            pre[i] = cur+1;
        }
        cur = pre[i];
    }
    cur = 0;
    for(int i = n-1; i>=0; i--)
    {
        if(in[i]<(*s2.begin()))
        {
            s2.erase((--s2.end()));
            suf[i] = cur;
        }
        else
        {
            s2.erase(--s2.lower_bound(in[i]));
            suf[i] = cur+1;
        }
        cur = suf[i];
    }
    ans = max(suf[0],pre[n-1]);
    for(int i = 0; i<n-1; i++)
    {
        ans = max(ans,pre[i]+suf[i+1]);
    }
    outfile << ans << endl;
}
