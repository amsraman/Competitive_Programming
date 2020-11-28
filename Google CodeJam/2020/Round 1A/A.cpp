#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n;
string p[50], ans;
pair<int,string> pre[50], suf[50];
bool pos;

string rem(string x)
{
    string ret = "";
    for(int i = 0; i<x.length(); i++)
        if(x[i]!='*')
            ret+=x[i];
    return ret;
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        ans = "", pos = true;
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> p[i];
        for(int i = 0; i<n; i++)
        {
            int p1, p2;
            for(int j = 0; j<p[i].length(); j++)
            {
                p1 = j;
                if(p[i][j]=='*')
                    j = p[i].length();
            }
            for(int j = p[i].length()-1; j>=0; j--)
            {
                p2 = j;
                if(p[i][j]=='*')
                    j = -1;
            }
            if(p1>p2)
                pre[i].s = "", suf[i].s = p[i];
            else
                pre[i].s = p[i].substr(0,p1), suf[i].s = p[i].substr(p2+1,p[i].length()-p2-1), ans+=rem(p[i].substr(p1,p2-p1+1));
            pre[i].f = pre[i].s.length(), suf[i].f = suf[i].s.length();
        }
        sort(pre,pre+n);
        sort(suf,suf+n);
        //do the prefix/suffix check
        for(int i = 0; i<n-1; i++)
            if(pre[i].s!=pre[i+1].s.substr(0,pre[i].f))
                pos = false;
        for(int i = 0; i<n-1; i++)
            if(suf[i].s!=suf[i+1].s.substr(suf[i+1].s.length()-suf[i].f,suf[i].f))
                pos = false;
        cout << "Case #" << cs+1 << ": ";
        if(pos)
            cout << pre[n-1].s+ans+suf[n-1].s << endl;
        else
            cout << "*" << endl;
    }
}
