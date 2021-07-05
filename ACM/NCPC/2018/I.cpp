#include <bits/stdc++.h>

using namespace std;

int n;
string s, tot = "0", names[1000], bets[1000];
vector<string> ans;

string add(string x, string y)
{
    if(x.length()<y.length())
        swap(x,y);
    while(y.length()<x.length())
        y = "0"+y;
    int carry = 0;
    string ret = "";
    for(int i = x.length()-1; i>=0; i--)
        ret = char('0'+((x[i]-'0')+(y[i]-'0')+carry)%10)+ret, carry = ((x[i]-'0')+(y[i]-'0')+carry)/10;
    if(carry>0)
        ret = char('0'+carry)+ret;
    return ret;
}

bool cmp(string x, string y)
{
    if(x.length()!=y.length())
        return (x.length()>y.length());
    for(int i = 0; i<x.length(); i++)
    {
        if(x[i]>y[i])
            return true;
        if(y[i]>x[i])
            return false;
    }
    return true;
}

int main()
{
    cin >> n >> s;
    for(int i = 0; i<n; i++)
        cin >> names[i] >> bets[i];
    for(int i = 0; i<n; i++)
        for(int j = i+1; j<n; j++)
            if(cmp(bets[i],bets[j]))
                swap(bets[i],bets[j]), swap(names[i],names[j]);
    for(int i = n-1; i>=0; i--)
        if(cmp(s,add(tot,bets[i])))
            ans.push_back(names[i]), tot = add(tot,bets[i]);
    if(tot!=s)
        ans.clear();
    cout << ans.size() << endl;
    for(string i: ans)
        cout << i << endl;
}