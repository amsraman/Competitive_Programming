/*
ID: adisund1
LANG: C++
TASK: friday
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int n, day = 4;
    int month[12] = {31,31,28,31,30,31,30,31,31,30,31,30};
    int ans[7] = {0,0,0,0,0,0,0};
    ifstream infile("friday.in");
    ofstream outfile("friday.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<12; j++)
        {
            day = day+month[j];
            if(j==2)
            {
                if((i%4==0)&&(i%400!=0)&&(i%400!=200)&&(i%400!=300))
                {
                    day++;
                }
            }
            ans[day%7]++;
        }
    }
    outfile << ans[0];
    for(int i = 1; i<7; i++)
    {
        outfile << " " << ans[i];
    }
    outfile << endl;
}
