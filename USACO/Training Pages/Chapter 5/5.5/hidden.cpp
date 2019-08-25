/*
ID: adityasund1
TASK: hidden
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int l, p1, p2 = 1, cnt;
string s, in;

int main()
{
    ifstream infile("hidden.in");
    ofstream outfile("hidden.out");
    infile >> l;
    while(infile>>in)
    {
        s+=in;
    }
    while(p2<=l)
    {
        cnt = 0;
        while((s[(p1+cnt)%l]==s[(p2+cnt)%l])&&(cnt<l))
        {
            cnt++;
        }
        if(cnt==l) break;
        if(s[(p1+cnt)%l]<s[(p2+cnt)%l])
        {
            p2 = p2+cnt+1;
        }
        else
        {
            p1 = p1+cnt+1;
        }
        if(p1==p2) p2++;
    }
    outfile << p1 << endl;
}
