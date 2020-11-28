#include <iostream>
#include <fstream>
#define MOD 1000000007

using namespace std;

int t, n, k, ac, bc, mdif, pow2[1000000], ans;
string s;

int main()
{
    ifstream fin("class_treasurer.txt");
    ofstream fout("output.txt");
    fin >> t;
    pow2[0] = 2;
    for(int i = 1; i<1000000; i++) pow2[i] = (2*pow2[i-1])%MOD;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> k >> s;
        ac = bc = mdif = ans = 0;
        for(int i = n-1; i>=0; i--)
        {
            if(s[i]=='A') ac++;
            if(s[i]=='B') bc++;
            int tdif = bc-ac-mdif;
            if((tdif>k)&&(s[i]=='B'))
            {
                ans = (ans+pow2[i])%MOD;
                ac++, bc--;
            }
            mdif = min(mdif,bc-ac);
        }
        fout << "Case #" << z+1 << ": " << ans << endl;
    }
}
