#include <fstream>
#include <iostream>
#include <string>
#define A 100000007
#define B 1000000007

using namespace std;

int main()
{
    ifstream infile("censor.in");
    ofstream outfile("censor.out");
    string r, s, w;
    infile >> s >> w;
    long long hsh[s.length()], mod[s.length()+1], rhsh[s.length()], whsh = 65+(w[0]-'a');
    hsh[0] = 65+(s[0]-'a');
    mod[0] = 1;
    for(int i = 1; i<w.length(); i++)
    {
        whsh = (whsh*A)%B;
        whsh = (whsh+65+(w[i]-'a'))%B;
    }
    if(whsh<0){whsh+=B;}
    for(int i = 1; i<s.length(); i++)
    {
        mod[i] = (mod[i-1]*A)%B;
        if(mod[i]<0){mod[i]+=B;}
        hsh[i] = ((hsh[i-1]*A)+65+(s[i]-'a'))%B;
    }
    mod[s.length()] = (mod[s.length()-1]*A)%B;
    if(mod[s.length()]<0){mod[s.length()]+=B;}
    for(int i = 0; i<s.length(); i++)
    {
        r+=s.substr(i,1);
        rhsh[r.size()-1] = ((r.size()>1)?(rhsh[r.size()-2]*A+65+(r[r.size()-1]-'a'))%B:(65+(r[r.size()-1]-'a'))%B);
        long long subhash = (r.size()>w.size())?(rhsh[r.size()-1]-(rhsh[r.size()-1-w.size()]*mod[w.size()])%B)%B:0;
        if(r.size()==w.size()){subhash = rhsh[r.size()-1];}
        if(subhash<0){subhash+=B;}
        if((r.size()>=w.size())&&(subhash==whsh))
        {
            r.resize(r.size()-w.length());
        }
    }
    outfile << r << endl;
}
