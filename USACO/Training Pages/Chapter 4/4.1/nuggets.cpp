/*
ID: adityasund1
TASK: nuggets
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int gcd(int a, int b)
{
    if((a==0)||(b==0))
    {
        return a+b;
    }
    return gcd(max(a,b)%min(a,b),min(a,b));
}

int main()
{
    ifstream infile("nuggets.in");
    ofstream outfile("nuggets.out");
    int n;
    bool z = true;
    set<int> s1, s2;
    infile >> n;
    int ar[n];
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(gcd(ar[i],ar[j])==1)
            {
                z = false;
            }
        }
    }
    if(z)
    {
        outfile << 0 << endl;
        return 0;
    }
    s1.insert(0);
    for(int i = 0; i<=65536; i++)
    {
        s2.insert(i);
    }
    for(int i = 0; i<n; i++)
    {
        set<int>::iterator it = s1.begin();
        while((*it)+ar[i]<=65536)
        {
            s1.insert(ar[i]+(*it));
            it++;
        }
    }
    s1.erase(0);
    set<int>::iterator it = s1.begin();
    for(int i = 0; i<s1.size(); i++)
    {
        s2.erase((*it));
        it++;
    }
    it = s2.end();
    outfile << *(--it) << endl;
}
