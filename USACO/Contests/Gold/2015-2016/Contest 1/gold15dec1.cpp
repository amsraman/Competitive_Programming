#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("cardgame.in");
    ofstream outfile("cardgame.out");
    int n;
    infile >> n;
    int p1[n], ba[n], p2[n], s[n];
    for(int i = 0; i<n; i++)
    {
        infile >> p1[i];
        s[i] = p1[i];
    }
    int a = n-1, b = 0;
    sort(s,s+n);
    for(int i = 2*n; i>0; i--)
    {
        if(i==s[a])
        {
            a--;
        }
        else
        {
            ba[b] = i;
            b++;
        }
    }
    sort(p1,p1+(n/2));
    sort(p1+(n/2),p1+n);
    a = 0;
    b = (n/2)-1;
    for(int i = (n/2)-1; i>=0; i--)
    {
        if(ba[a]>p1[i])
        {
            p2[i] = ba[a];
            a++;
        }
        else
        {
            p2[i] = ba[b];
            b--;
        }
    }
    a = n/2;
    b = n-1;
    for(int i = n/2; i<n; i++)
    {
        if(ba[b]<p1[i])
        {
            p2[i] = ba[b];
            b--;
        }
        else
        {
            p2[i] = ba[a];
            a++;
        }
    }
    int ans = 0;
    for(int i = 0; i<(n/2); i++)
    {
        if(p2[i]>p1[i])
        {
            ans++;
        }
    }
    for(int i = n/2; i<n; i++)
    {
        if(p2[i]<p1[i])
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
