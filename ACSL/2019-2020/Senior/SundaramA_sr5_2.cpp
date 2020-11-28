#include <bits/stdc++.h>

using namespace std;

int t = 5, r1, r2, len[201][201], maxlen[200], maxs, ans;
string a, b;

string preprocess(string x)
{
    for(int i = 0; i<x.length(); i++)
        if(!isalpha(x[i]))
            x.erase(i,1), i--;
    for(int i = 0; i<x.length(); i++)
        x[i] = char(toupper(x[i]));
    return x;
}

void lcs(string x, string y)
{
    memset(len,0,sizeof(len));
    memset(maxlen,0,sizeof(maxlen));
    int n = x.length(), m = y.length();
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            if(x[i]==y[j])
                len[i+1][j+1] = len[i][j]+1, maxlen[i] = max(maxlen[i],len[i+1][j+1]);
    r1 = r2 = maxs = 0;
    for(int i = 0; i<n; i++)
        maxs = max(maxs,maxlen[i]);
    for(int i = n-1; i>=0; i--)
        if(maxlen[i]==maxs)
            r1 = i;
    for(int i = 0; i<n; i++)
        if((maxlen[i]==maxs)&&(x.substr(i-maxs+1,maxs)<x.substr(r1-maxs+1,maxs)))
            r1 = i;
    for(int i = m; i>0; i--)
        if(len[r1+1][i]==maxs)
            r2 = i-1;
}

void f(string x, string y)
{
    lcs(x,y);
    if(!maxs)
        return;
    ans+=maxs;
    string s1 = x.substr(0,r1-maxs+1), s2 = y.substr(0,r2-maxs+1), s3 = x.substr(r1+1,x.length()-r1), s4 = y.substr(r2+1,y.length()-r2);
    f(s1,s2);
    f(s3,s4);
}

int main()
{
    freopen("D:/2srtest.txt","r",stdin);
    while(t--)
    {
        ans = 0;
        getline(cin,a);
        getline(cin,b);
        f(preprocess(a),preprocess(b));
        cout << ans << endl;
    }
}
