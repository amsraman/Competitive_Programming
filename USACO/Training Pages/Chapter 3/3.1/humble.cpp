/*
ID: adityasund1
TASK: humble
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main()
{
    ifstream infile("humble.in");
    ofstream outfile("humble.out");
    int n, k;
    set<int> s;
    infile >> k >> n;
    int p[k];
    for(int i = 0; i<k; i++)
    {
        infile >> p[i];
        s.insert(p[i]);
    }
    for(int i = 0; i<k; i++)
    {
        set<int>::iterator it = s.begin();
        while(true)
        {
            int v = (*it)*p[i];
            if(v<0)
            {
                break;
            }
            if(s.size()==n)
            {
                if(v>*(--s.end()))
                {
                    break;
                }
                if(s.count(v)==0)
                {
                    s.erase(--s.end());
                }
            }
            s.insert(v);
            it++;
        }
    }
    outfile << *(--s.end()) << endl;
}
