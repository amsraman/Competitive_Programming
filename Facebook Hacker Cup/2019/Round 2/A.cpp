#include <iostream>
#include <fstream>

using namespace std;

int t, n, m, k, a, b, r1, c1, r2, c2;

int main()
{
    ifstream fin("on_the_run.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> m >> k >> a >> b >> r1 >> c1;
        fout << "Case #" << z+1 << ": ";
        if(k==1)
        {
            fout << 'N' << endl;
        }
        else
        {
            fin >> r2 >> c2;
            fout << ((((a+b)%2==(r1+c1)%2)&&((a+b)%2==(r2+c2)%2))?('Y'):('N')) << endl;
        }
    }
}
