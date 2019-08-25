#include <iostream>
#include <fstream>

using namespace std;

int t, b;
string l;

int main()
{
    ifstream fin("leapfrog_ch_.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> l;
        b = 0;
        for(int i = 0; i<l.length(); i++)
        {
            if(l[i]=='B') b++;
        }
        fout << "Case #" << z+1 << ": " << (((2*b+1>=l.length())&&(l.length()-1!=b))?('Y'):('N')) << endl;
    }
}
