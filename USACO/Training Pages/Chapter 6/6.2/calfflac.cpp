/*
ID: adityasund1
TASK: calfflac
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int go[40000], p[40001], maxl;
string s, ck = "#", temp, ans;

int main()
{
    freopen("calfflac.in","r",stdin);
    freopen("calfflac.out","w",stdout);
    while(getline(cin,temp))
        s+=temp, s+='\n';
    for(int i = 0; i<s.length(); i++)
        if(isalpha(s[i]))
            ck+=toupper(s[i]), ck+='#', go[ck.length()-2] = i;
    // manacher's
    int c = 0, r = -1, rad;
    for(int i = 0; i<ck.length(); i++)
    {
        if(i<=r)
            rad = min(p[2*c-i],r-i);
        else
            rad = 0;
        while((i+rad<ck.length()-1)&&(i>rad)&&(ck[i-rad-1]==ck[i+rad+1]))
            rad++;
        p[i] = rad, maxl = max(maxl,p[i]);
        if(i+rad-1>r)
            c = i, r = i+rad-1;
    }
    for(int i = ck.length()-1; i>=0; i--)
        if(p[i]==maxl)
            ans = s.substr(go[i-p[i]+1],go[i+p[i]-1]-go[i-p[i]+1]+1);
    cout << maxl << endl << ans << endl;
}