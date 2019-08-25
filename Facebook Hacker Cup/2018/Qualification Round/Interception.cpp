#include <iostream>
#include <fstream>

using namespace std;

int t, n, p;

int main()
{
    ifstream fin("interception.txt");
    ofstream fout("out.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n;
        for(int i = 0; i<=n; i++)
        {
            fin >> p;
        }
        if(n%2==1)
        {
            fout << "Case #" << z+1 << ": " << 1 << endl << "0.0" << endl;
        }
        else
        {
            fout << "Case #" << z+1 << ": " << 0 << endl;
        }
    }
}
