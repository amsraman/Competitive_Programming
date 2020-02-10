/*
ID: adisund1
LANG: C++
TASK: wormhole
*/
#include <fstream>
#include <iostream>

using namespace std;

int m(int a)
{
    int ret = 1;
    for(int i = 1; i<a/2; i++)
    {
        ret = ret*(2*i+1);
    }
    return ret;
}

int check(int y[], int next[], int n)
{
    int p;
    for(int i = 0; i<n; i++)
    {
        p = i;
        for(int j = 0; j<n; j++)
        {
            p = next[p];
            if(p==-1)
            {
                break;
            }
            else
            {
                p = y[p];
            }
        }
        if(p!=-1)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
	int n, ans = 0;
	ifstream infile("wormhole.in");
	ofstream outfile("wormhole.out");
	infile >> n;
	int x[n], y[n], next[n];
	for(int i = 0; i<n; i++)
	{
	    infile >> x[i] >> y[i];
	}
	int mini, use;
	for(int i = 0; i<n; i++)
	{
	    mini = 100000000000;
	    use = -1;
	    for(int j = 0; j<n; j++)
	    {
	        if(j!=i)
	        {
	            if((y[i]==y[j])&&(x[j]>x[i]))
	            {
	                if(x[j]-x[i]<mini)
	                {
	                    use = j;
	                    mini = x[j]-x[i];
	                }
	            }
	        }
	    }
	    next[i] = use;
	}
	int n1;
	int pai[n], us[n], temp, init, fina, temp2;
	for(int i = 0; i<m(n); i++)
	{
	    temp = i;
	    for(int j = 0; j<n; j++)
        {
            us[j] = -1;
            pai[j] = -1;
        }
        n1 = n;
        while(n1>0)
        {
            init = 0;
            while(us[init]!=-1)
            {
                init++;
            }
            fina = init+1;
            us[init] = 1;
            temp2 = 0;
            while(temp2<temp/m(n1-2))
            {
                if(us[fina]==-1)
                {
                    temp2++;
                }
                fina++;
            }
            if(us[fina]!=-1)
            {
                while(us[fina]!=-1)
                {
                    fina++;
                }
            }
            temp = temp - (temp/m(n1-2))*m(n1-2);
            us[fina] = 1;
            pai[init] = fina;
            pai[fina] = init;
            n1 = n1-2;
        }
        if(check(pai,next,n)==1)
        {
            ans++;
        }
	}
	outfile << ans << endl;
	return 0;
}
