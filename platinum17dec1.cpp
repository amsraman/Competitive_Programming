#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
typedef long long ll;

using namespace std;

int n, id[200000], r[200000][19], suf[200000], lcp[200000], endst[100000], maxs[100000], cnt;
ll ans;
string in[100000], str;
pair<pair<int,int>,int> s[200000];

int flcp(int a, int b)
{
    int l = 0;
    for(int i = 18; i>=0; i--)
    {
        if((r[a][i]==r[b][i])&&(r[a][i]!=0))
        {
            a+=(1<<i);
            b+=(1<<i);
            l+=(1<<i);
        }
    }
    return l;
}

int main()
{
    ifstream infile("standingout.in");
    ofstream outfile("standingout.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        str+=in[i];
        str+="$";
        maxs[i] = n;
    }
    for(int i = 0; i<str.length(); i++)
    {
        if(str[i]=='$')
        {
            id[i] = -1;
            endst[cnt] = i-1;
            cnt++;
        }
        else
        {
            id[i] = cnt;
        }
    }
    for(int i = 0; i<str.length()-1; i++)
    {
        r[i][0] = (str[i]-'A')+1;
        s[i] = {{r[i][0],str[i+1]-'A'},i};
    }
    r[str.length()-1][0] = str[str.length()-1]-'A';
    s[str.length()-1] = {{r[str.length()-1][0],-1},str.length()-1};
    for(int i = 1; (1<<i)<=str.length(); i++)
    {
        sort(s,s+str.length());
        r[s[0].second][i] = 1;
        for(int j = 1; j<str.length(); j++)
        {
            if((s[j].first.first==s[j-1].first.first)&&(s[j].first.second==s[j-1].first.second)){r[s[j].second][i] = r[s[j-1].second][i];}
            else{r[s[j].second][i] = r[s[j-1].second][i]+1;}
        }
        for(int j = 0; j<str.length(); j++)
        {
            if(s[j].second+(1<<i)<str.length()){s[j] = {{r[s[j].second][i],r[s[j].second+(1<<i)][i]},s[j].second};}
            else{s[j] = {{r[s[j].second][i],-1},s[j].second};}
        }
    }
    for(int i = 0; i<str.length(); i++){suf[i] = s[i].second;}
    for(int i = n; i<str.length(); i++)
    {
        if(id[suf[i-1]]!=id[suf[i]]){maxs[id[suf[i]]] = i;}
        if(maxs[id[suf[i]]]!=n){lcp[suf[i]] = min(flcp(suf[maxs[id[suf[i]]]-1],suf[i]),endst[id[suf[i]]]-suf[i]+1);}
    }
    for(int i = str.length()-2; i>=n; i--){lcp[suf[i]] = max(lcp[suf[i]],min(flcp(suf[i+1],suf[i]),min(endst[id[suf[i]]]-suf[i]+1,endst[id[suf[i+1]]]-suf[i+1]+1)));}
    ans = ll(in[id[0]].length())*ll(in[id[0]].length()+1)/2;
    for(int i = 0; i<str.length()-1; i++)
    {
        if(id[i]==-1)
        {
            outfile << ans << endl;
            ans = ll(in[id[i+1]].length())*ll(in[id[i+1]].length()+1)/2;
        }
        else
        {
            ans-=ll(lcp[i]);
        }
    }
    outfile << ans << endl;
}
