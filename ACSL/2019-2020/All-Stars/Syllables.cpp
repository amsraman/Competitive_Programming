#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, ans, p1, p2, mm, sl, vow[26];
string s, pre[6] = {"co","de","dis","pre","re","un"}, suf[5] = {"age","ful","ing","less","ment"};
vector<pair<int,int> > flags;

bool isPref(int x)
{
    if((pre[x].length()<s.length())&&((s.substr(0,pre[x].length())==pre[x])))
        return true;
    return false;
}

bool isSuf(int x)
{
    if((suf[x].length()<s.length())&&((s.substr(n-suf[x].length(),suf[x].length())==suf[x])))
        return true;
    return false;
}

int main()
{
    cin >> s;
    string origs = s;
    n = s.length(), p1 = 0, p2 = n;
    for(int i = 0; i<6; i++)
        if(isPref(i))
            p1 = pre[i].length(), ans+=pre[i].length(), mm++;
    for(int i = 0; i<5; i++)
        if(isSuf(i))
            p2 = n-suf[i].length(), sl = suf[i].length();
    if(p2!=n)
        s.erase(p2,n-p2);
    s.erase(0,p1);
    string vowstr = "";
    while(s.length()!=0)
    {
        bool done = false;
        char k = s[0];
        if((k=='a')||(k=='e')||(k=='i')||(k=='o')||(k=='u'))
        {
            vowstr+=k;
            s.erase(0,1);
            done = true;
        }
        else
        {
            if(vowstr.length()!=0)
                flags.push_back({0,vowstr.length()});
            vowstr = "";
            if(s.length()>1)
            {
                string hi = s.substr(0,2);
                if((hi=="ch")||(hi=="ck")||(hi=="ph")||(hi=="sh")||(hi=="th")||(hi=="wh")||(hi=="wr"))
                {
                    flags.push_back({1,2});
                    s.erase(0,2);
                    done = true;
                }
            }
            if(!done)
            {
                flags.push_back({1,1});
                s.erase(0,1);
                done = true;
            }
        }
    }
    if(vowstr.length()!=0)
        flags.push_back({0,vowstr.length()});
    for(int i = 0; i<int(flags.size()); i++)
    {
        p1+=flags[i].s;
        if(flags[i].f==0)
        {
            if((i<int(flags.size())-2)&&(flags[i+2].f==0))
                ans+=(p1+mm), mm++;
        }
        else
        {
            if((i!=0)&&(i<int(flags.size())-2)&&(flags[i+1].f==1))
                ans+=(p1+mm), mm++;
        }
    }
    if(sl!=0)
        ans+=(n-sl+mm);
    cout << ans << endl;
}
