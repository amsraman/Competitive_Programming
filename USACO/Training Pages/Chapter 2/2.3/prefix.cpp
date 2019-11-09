/*
ID: adityasund1
TASK: prefix
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool v[200001] = {false};
int ma[200001];
string in = "";
vector<string> prim;

int solve(int a)
{
    if(v[a])
    {
        return ma[a];
    }
    int ret = a;
    for(int i = 0; i<prim.size(); i++)
    {
        if((prim[i].size()<=a)&&(prim[i]==in.substr(in.size()-a,prim[i].size())))
        {
            ret = min(ret,solve(a-prim[i].size()));
        }
    }
    return ret;
}

int main()
{
    ifstream infile("prefix.in");
    ofstream outfile("prefix.out");
    string a;
    infile >> a;
    while(a!=".")
    {
        prim.push_back(a);
        infile >> a;
    }
    infile.ignore();
    while(getline(infile,a))
    {
        in+=a;
    }
    for(int i = 0; i<in.size(); i++)
    {
        ma[i] = solve(i);
        v[i] = true;
    }
    outfile << in.size()-solve(in.size()) << endl;
}
