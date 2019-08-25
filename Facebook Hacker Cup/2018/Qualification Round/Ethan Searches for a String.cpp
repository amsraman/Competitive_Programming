#include <iostream>
#include <fstream>

using namespace std;

int t;
string a;

int main()
{
    ifstream fin("ethan_searches_for_a_string.txt");
    ofstream fout("out.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> a;
        int ind = 1;
        bool pattern = true;
        while((a[ind]!=a[0])&&(ind<a.length()))
        {
            ind++;
        }
        for(int i = 0; i<a.length(); i++)
        {
            if(a[i]!=a[i%ind])
            {
                pattern = false;
            }
        }
        if((ind==a.length())||(pattern))
        {
            fout << "Case #" << z+1 << ": Impossible" << endl;
        }
        else
        {
            fout << "Case #" << z+1 << ": " << a.substr(0,ind)+a << endl;
        }
    }
}
/*

1. Find first instance of first letter
2. Verify that the pattern until this instance does not persist throughout
3. Add the substring from 0 to index-1 to the beginning

impossible if:
1. First letter does not appear again
2. The string is periodic
*/
