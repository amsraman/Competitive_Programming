/*
ID: adityasund1
TASK: ariprog
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool check(int a, int d, int i, bool used[], int n)
{
    if(i==n-1)
    {
        return true;
    }
    if(used[a+d])
    {
        check(a+d,d,i+1,used,n);
    }
    else
    {
        return false;
    }
}

int main()
{
    int m, n;
    ifstream infile("ariprog.in");
    ofstream outfile("ariprog.out");
    infile >> n;
    infile >> m;
    bool used[2*m*m+1] = {false};
    int b[2*m*m+1], c = 0;
    for(int i = 0; i<=m; i++)
    {
        for(int j = 0; j<=m; j++)
        {
            int p = i*i + j*j;
            if(used[p]==false)
            {
                b[c] = p;
                c++;
                used[p] = true;
            }
        }
    }
    sort(b,b+c);
    int ans1[2*m*m], ans2[2*m*m], cnt = 0;
    for(int i = 0; i<c-1; i++)
    {
        int j = i+1;
        int d = b[j] - b[i];
        while(b[i]+(n-1)*d<=b[c-1])
        {
            if(check(b[i],d,0,used,n))
            {
                ans1[cnt] = b[i];
                ans2[cnt] = d;
                cnt++;
            }
            j++;
            d = b[j]-b[i];
        }
    }
    if(cnt==0)
    {
        outfile << "NONE" << endl;
    }
    else
    {
        int temp;
        for(int i = 0; i<cnt; i++)
        {
            for(int j = i+1; j<cnt; j++)
            {
                if(ans2[j]<ans2[i])
                {
                    temp = ans2[j];
                    ans2[j] = ans2[i];
                    ans2[i] = temp;
                    temp = ans1[j];
                    ans1[j] = ans1[i];
                    ans1[i] = temp;
                }
                else if(ans2[j]==ans2[i])
                {
                    if(ans1[j]<ans1[i])
                    {
                        temp = ans2[j];
                        ans2[j] = ans2[i];
                        ans2[i] = temp;
                        temp = ans1[j];
                        ans1[j] = ans1[i];
                        ans1[i] = temp;
                    }
                }
            }
        }
        for(int i = 0; i<cnt; i++)
        {
            outfile << ans1[i] << " " << ans2[i] << endl;
        }
    }
    return 0;
}
