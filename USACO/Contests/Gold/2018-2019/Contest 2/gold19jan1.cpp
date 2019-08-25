#include <fstream>
#include <iostream>
#define MOD 1000000007
#define INF 0xfffffffffffffff

using namespace std;

int n, m, k;
char z;
int s[5000], c[5000], sch[26];
long long syl[5001], cl[5000], mult, add, ans = 1;

int main()
{
    ifstream infile("poetry.in");
    ofstream outfile("poetry.out");
    infile >> n >> m >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> s[i] >> c[i];
    }
    for(int i = 0; i<m; i++)
    {
        infile >> z;
        sch[(z-'A')]++;
    }
    syl[0] = 1;
    for(int i = 0; i<k; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(i+s[j]<=k)
            {
                syl[i+s[j]] = ((syl[i+s[j]]+syl[i])%MOD+MOD)%MOD;
            }
        }
    }
    for(int i = 0; i<n; i++)//number of ways to end in scheme i
    {
        cl[c[i]-1] = ((cl[c[i]-1]+syl[k-s[i]])%MOD+MOD)%MOD;
    }
    for(int i = 0; i<26; i++)//for each specified pattern
    {
        if(sch[i]!=0)
        {
            mult = 0;
            for(int j = 0; j<n; j++)//for each possible rhyme class
            {
                add = 1;
                int exp = sch[i], curexp = 0;
                long long curmult = cl[j];
                while(exp!=0)
                {
                    if((1<<curexp)==((exp)&(-exp)))
                    {
                        add = ((add*curmult)%MOD+MOD)%MOD;
                        exp-=(1<<curexp);
                    }
                    curmult = ((curmult*curmult)%MOD+MOD)%MOD;
                    curexp++;
                }
                mult = ((mult+add)%MOD+MOD)%MOD;
            }
            ans = ((ans*mult)%MOD+MOD)%MOD;
        }
    }
    outfile << ans << endl;
}
