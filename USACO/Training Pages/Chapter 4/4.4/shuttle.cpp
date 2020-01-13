/*
ID: adityasund1
TASK: shuttle
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("shuttle.in");
    ofstream outfile("shuttle.out");
    int n;
    vector<int> ans;
    infile >> n;
    int ar[2*n+1];
    for(int i = 0; i<n; i++){ar[i] = 1;}
    ar[n] = 0;
    for(int i = n+1; i<2*n+1; i++){ar[i] = 2;}
    int cp = n, e1 = 0, e2 = 2*n;
    for(int i = 0; i<2*n-1; i++)
    {
        if(i%2==0)
        {
            if(cp==e1)
            {
                ar[cp] = ar[cp+1];
                ar[cp+1] = 0;
                ans.push_back(cp+2);
                cp++;
                e1++;
            }
            else
            {
                ar[cp] = ar[cp-1];
                ar[cp-1] = 0;
                ans.push_back(cp);
                if(cp==e2){e2--;}
                cp--;
            }
            while((cp<2*n-1)&&(ar[cp+1]!=ar[cp+2]))
            {
                if(cp==e1){e1++;}
                ans.push_back(cp+3);
                ar[cp] = ar[cp+2];
                ar[cp+2] = 0;
                cp+=2;
            }
        }
        else
        {
            if(cp==e2)
            {
                ar[cp] = ar[cp-1];
                ar[cp-1] = 0;
                ans.push_back(cp);
                cp--;
                e2--;
            }
            else
            {
                ar[cp] = ar[cp+1];
                ar[cp+1] = 0;
                ans.push_back(cp+2);
                if(cp==e1){e1++;}
                cp++;
            }
            while((cp>1)&&(ar[cp-1]!=ar[cp-2]))
            {
                if(cp==e2){e2--;}
                ans.push_back(cp-1);
                ar[cp] = ar[cp-2];
                ar[cp-2] = 0;
                cp-=2;
            }
        }
    }
    ans.push_back(n+1);
    outfile << ans[0];
    for(int i = 1; i<ans.size(); i++)
    {
        if(i%20==0)
        {
            outfile << endl << ans[i];
        }
        else
        {
            outfile << " " << ans[i];
        }
    }
    outfile << endl;
}
