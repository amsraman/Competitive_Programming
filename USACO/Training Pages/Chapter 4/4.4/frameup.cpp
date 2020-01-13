/*
ID: adityasund1
TASK: frameup
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int h, w, minh[26], maxh[26], minw[26], maxw[26], d[26], co;
char ar[30][30];
bool o[26][26], v[26];
string cur, alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
vector<string> ans;

void dfs(int a)
{
    if(a==co)
    {
        ans.push_back(cur);
        return;
    }
    for(int i = 0; i<26; i++)
    {
        if((v[i])&&(d[i]==0))
        {
            for(int j = 0; j<26; j++)
            {
                if(o[j][i]){d[j]--;}
            }
            cur = alpha.substr(i,1)+cur;
            v[i] = false;
            dfs(a+1);
            v[i] = true;
            cur = cur.substr(1,cur.size()-1);
            for(int j = 0; j<26; j++)
            {
                if(o[j][i]){d[j]++;}
            }
        }
    }
}

int main()
{
    ifstream infile("frameup.in");
    ofstream outfile("frameup.out");
    infile >> h >> w;
    for(int i = 0; i<26; i++){minw[i] = minh[i] = 1000;}
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            infile >> ar[i][j];
            if(ar[i][j]!='.')
            {
                if(!v[ar[i][j]-'A'])
                {
                    v[ar[i][j]-'A'] = true;
                    co++;
                }
                minh[ar[i][j]-'A'] = min(minh[ar[i][j]-'A'],i);
                maxh[ar[i][j]-'A'] = max(maxh[ar[i][j]-'A'],i);
                minw[ar[i][j]-'A'] = min(minw[ar[i][j]-'A'],j);
                maxw[ar[i][j]-'A'] = max(maxw[ar[i][j]-'A'],j);
            }
        }
    }
    for(int i = 0; i<26; i++)
    {
        if(v[i])
        {
            for(int j = minw[i]; j<=maxw[i]; j++)
            {
                o[i][ar[minh[i]][j]-'A'] = true;
                o[i][ar[maxh[i]][j]-'A'] = true;
            }
            for(int j = minh[i]; j<=maxh[i]; j++)
            {
                o[i][ar[j][minw[i]]-'A'] = true;
                o[i][ar[j][maxw[i]]-'A'] = true;
            }
        }
    }
    for(int i = 0; i<26; i++)
    {
        for(int j = 0; j<26; j++)
        {
            if((o[i][j])&&(i!=j)){d[i]++;}
        }
    }
    dfs(0);
    sort(ans.begin(),ans.end());
    for(int i = 0; i<ans.size(); i++){outfile << ans[i] << endl;}
}
