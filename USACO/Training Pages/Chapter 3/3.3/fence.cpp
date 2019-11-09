/*
ID: adityasund1
TASK: fence
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

multiset<int> g[500];
vector<int> circ;
bool v[500] = {false};

void circuit(int a)
{
    while(g[a].size()!=0)
    {
        multiset<int>::iterator it = g[a].begin();
        int n = *it;
        g[n].erase(g[n].find(a));
        g[a].erase(g[a].find(n));
        circuit(n);
    }
    circ.push_back(a);
}

int main()
{
    ifstream infile("fence.in");
    ofstream outfile("fence.out");
    int f, a, b;
    bool z = false;
    infile >> f;
    for(int i = 0; i<f; i++)
    {
        infile >> a >> b;
        v[a-1] = v[b-1] = true;
        g[a-1].insert(b-1);
        g[b-1].insert(a-1);
    }
    for(int i = 0; i<500; i++)
    {
        if(g[i].size()%2==1)
        {
            z = true;
        }
    }
    for(int i = 0; i<500; i++)
    {
        if((v[i])&&(((z)&&(g[i].size()%2==1))||((!z)&&(g[i].size()%2==0))))
        {
            circuit(i);
            for(int i = circ.size()-1; i>=0; i--)
            {
                outfile << circ[i]+1 << endl;
            }
            return 0;
        }
    }
}
