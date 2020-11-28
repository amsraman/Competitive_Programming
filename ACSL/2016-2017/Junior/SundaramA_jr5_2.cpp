#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
	string a;
	string pb;
	int n, z;
	for(int k = 0; k<5; k++)
    {
    n=0;
	cout << "Enter digit string " << k+1 << ":\n";
	getline(cin, a);
	cout << endl;
	string x[a.length()], y[a.length()];
	x[0] = a.substr(0,1);
	y[0] = a.substr(0,1);
    a.erase(0,1);
    while(a.length()>=y[n].length())
    {
        for(int i = 1; i<=a.length(); i++)
        {
            if(atoi(a.substr(0,i).c_str())>atoi(x[n].c_str()))
            {
                x[n+1] = a.substr(0,i);
                y[n+1] = a.substr(0,i);
                n++;
                a.erase(0,i);
                i = 100;
                z = 0;
                pb = y[n];
                while(pb[0]=='0')
                {
                    pb.erase(0,1);
                }
                y[n] = pb;
            }
            else if (i==a.length())
            {
                if(a.length()==x[n].length())
                {
                    a.erase();
                }
                else if(atoi(a.c_str())<=atoi(x[n].c_str()))
                {
                    a.erase();
                }
            }
        }
    }
    for(int j = 0; j<=n; j++)
    {
        cout << x[j] << " ";
    }
    cout << endl << endl;
	}
}
