#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, co, rc1, rc2, h1, h2, v1, v2, ans;
bool a[26], v[20][20];
string ar[20];
vector<pair<pair<int,int>,pair<int,int> > > vec;

void dfs(int a, int b)
{
    v[a][b] = true;
    if((a>0)&&(!v[a-1][b])&&(ar[a-1][b]==ar[a][b])){dfs(a-1,b);}
    if((a<n-1)&&(!v[a+1][b])&&(ar[a+1][b]==ar[a][b])){dfs(a+1,b);}
    if((b>0)&&(!v[a][b-1])&&(ar[a][b-1]==ar[a][b])){dfs(a,b-1);}
    if((b<n-1)&&(!v[a][b+1])&&(ar[a][b+1]==ar[a][b])){dfs(a,b+1);}
}

int main()
{
    ifstream infile("where.in");
    ofstream outfile("where.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = i; j<n; j++)
        {
            for(int k = 0; k<n; k++)
            {
                for(int l = k; l<n; l++)
                {
                    for(int m = 0; m<26; m++){a[m] = false;}
                    co = 0;
                    for(int m = i; m<=j; m++)
                    {
                        for(int o = k; o<=l; o++)
                        {
                            if(!a[ar[m][o]-'A'])
                            {
                                a[ar[m][o]-'A'] = true;
                                co++;
                            }
                        }
                    }
                    if(co==2)
                    {
                        rc1 = rc2 = 0;
                        for(int m = i; m<=j; m++){for(int o = k; o<=l; o++){v[m][o] = false;}}
                        for(int m = i; m<=j; m++)
                        {
                            for(int o = k; o<=l; o++)
                            {
                                if(!v[m][o])
                                {
                                    dfs(m,o);
                                    if(ar[m][o]==ar[i][k]){rc1++;}
                                    else{rc2++;}
                                }
                            }
                        }
                        if(((rc1==1)&&(rc2>1))||((rc1>1)&&(rc2==1))){vec.push_back({{i,j},{k,l}});}
                    }
                }
            }
        }
    }
    for(int i = vec.size()-1; i>=0; i--)
    {
        for(int j = 0; j<vec.size(); j++)
        {
            if((j!=i)&&(vec[j].first.first<=vec[i].first.first)&&(vec[j].first.second>=vec[i].first.second)&&(vec[j].second.first<=vec[i].second.first)&&(vec[j].second.second>=vec[i].second.second))
            {
                ans--;
                break;
            }
        }
        ans++;
    }
    outfile << ans << endl;
}
