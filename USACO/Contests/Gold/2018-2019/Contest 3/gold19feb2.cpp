#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, in[100000], base[100000], p1, p2, last_placed;
vector<int> item[100000];

int main()
{
    ifstream fin("dishes.in");
    ofstream fout("dishes.out");
    fin >> n;
    for(int i = 0; i<n; i++)
    {
        fin >> in[i];
    }
    base[0] = in[0];
    item[0].push_back(in[0]);
    for(int i = 1; i<n; i++)
    {
        if(in[i]<last_placed)
        {
            fout << i << endl;
            return 0;
        }
        if(in[i]>base[p2])
        {
            p2++;
            base[p2] = in[i];
            item[p2].push_back(in[i]);
            continue;
        }
        int l = p1, g = p2;
        while(l<g)
        {
            int mid = (l+g)/2;
            if(base[mid]<in[i])
            {
                l = mid+1;
            }
            else
            {
                g = mid;
            }
        }
        if(in[i]>item[l][item[l].size()-1])
        {
            p1 = l;
            while(in[i]>item[l][item[l].size()-1])
            {
                last_placed = item[l][item[l].size()-1];
                item[l].pop_back();
            }
        }
        item[l].push_back(in[i]);
    }
}
