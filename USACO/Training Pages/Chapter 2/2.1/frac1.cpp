/*
ID: adisund1
LANG: C++
TASK: frac1
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    int r = 1;
    for(int i = 2; i<=min(a,b); i++)
    {
        if((a%i==0)&&(b%i==0))
        {
            r = i;
        }
    }
    return r;
}

int main()
{
    int n;
    ifstream infile("frac1.in");
    ofstream outfile("frac1.out");
    infile >> n;
    vector<int> nu;
    vector<int> de;
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<i; j++)
        {
            if(gcd(i,j)==1)
            {
                nu.push_back(j);
                de.push_back(i);
            }
        }
    }
    int t1, t2;
    for(int i = 1; i<nu.size(); i++)
    {
        int j = i;
        while((j>0)&&(nu[j-1]*de[j]>nu[j]*de[j-1]))
        {
            t1 = nu[j-1];
            t2 = de[j-1];
            nu[j-1] = nu[j];
            de[j-1] = de[j];
            nu[j] = t1;
            de[j] = t2;
            j--;
        }
    }
    outfile << "0/1" << endl;
    for(int i = 0; i<nu.size(); i++)
    {
        outfile << nu[i] << "/" << de[i] << endl;
    }
    outfile << "1/1" << endl;
}
