#include <iostream>
#include <fstream>

using namespace std;

int t, k, n;
long long v;
string attraction[50];

int main()
{
    ifstream fin("tourist.txt");
    ofstream fout("out.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> k >> v;
        for(int i = 0; i<n; i++)
        {
            fin >> attraction[i];
        }
        v = (((v-1)%n)*k)%n;
        fout << "Case #" << z+1 << ": ";
        for(int i = 0; i<(k-n+v); i++)
        {
            fout << attraction[i] << " ";
        }
        for(int i = v; i<min(n,int(v)+k); i++)
        {
            fout << attraction[i] << " ";
        }
        fout << endl;
    }
}
