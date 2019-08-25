/*
ID: adityasund1
TASK: twofive
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int pos[26];
long long n, dp[6][6][6][6][6], ans1 = 1;
char z;
string in, ans2;
bool used[26], v[6][6][6][6][6];

bool valid(int a, int c)
{
    return (!used[c]||(used[c]&&a==pos[c]));
}

long long ff(int a, int b, int c, int d, int e, int f)
{
    if(v[a][b][c][d][e]) return dp[a][b][c][d][e];
    if(f==25) return 1;
    v[a][b][c][d][e] = 1;
    long long ret = 0;
    if(valid(a,f)&&(a<5)) ret+=ff(a+1,b,c,d,e,f+1);
    if(valid(b+5,f)&&(b<5)&&(b<a)) ret+=ff(a,b+1,c,d,e,f+1);
    if(valid(c+10,f)&&(c<5)&&(c<b)) ret+=ff(a,b,c+1,d,e,f+1);
    if(valid(d+15,f)&&(d<5)&&(d<c)) ret+=ff(a,b,c,d+1,e,f+1);
    if(valid(e+20,f)&&(e<5)&&(e<d)) ret+=ff(a,b,c,d,e+1,f+1);
    dp[a][b][c][d][e] = ret;
    return ret;
}

int main()
{
    ifstream infile("twofive.in");
    ofstream outfile("twofive.out");
    infile >> z;
    if(z=='N')
    {
        infile >> n;
        for(int i = 0; i<25; i++)
        {
            for(int j = 0; j<26; j++)
            {
                if(!used[j])
                {
                    for(int k = 0; k<6*6*6*6*6; k++) dp[k/1296][(k%1296)/216][(k%216)/36][(k%36)/6][k%6] = v[k/1296][(k%1296)/216][(k%216)/36][(k%36)/6][k%6] = 0;
                    used[j] = true;
                    pos[j] = i;
                    long long num = ff(0,0,0,0,0,0);
                    if(num<n)
                    {
                        n-=num;
                        used[j] = false;
                    }
                    else
                    {
                        ans2+=char('A'+j);
                        break;
                    }
                }
            }
        }
        outfile << ans2 << endl;
    }
    else
    {
        infile >> in;
        for(int i = 0; i<25; i++)
        {
            for(int j = 0; j<(in[i]-'A'); j++)
            {
                if(!used[j])
                {
                    used[j] = true;
                    pos[j] = i;
                    for(int k = 0; k<6*6*6*6*6; k++) dp[k/1296][(k%1296)/216][(k%216)/36][(k%36)/6][k%6] = v[k/1296][(k%1296)/216][(k%216)/36][(k%36)/6][k%6] = 0;
                    ans1+=ff(0,0,0,0,0,0);
                    used[j] = false;
                    pos[j] = 0;
                }
            }
            used[in[i]-'A'] = true;
            pos[in[i]-'A'] = i;
        }
        outfile << ans1 << endl;
    }
}
