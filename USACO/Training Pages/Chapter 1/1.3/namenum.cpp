/*
ID: adityasund1
LANG: C++
TASK: namenum
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int len, counter = 0;
    string inp;
    ifstream infile("namenum.in");
    ifstream name("dict.txt");
    ofstream outfile("namenum.out");
    infile >> inp;
    len = inp.length();
    string opt[len];
    for(int i = 0; i<len; i++)
    {
       switch(inp[i])
       {
        case '2':
            opt[i] = "ABC";
            break;
        case '3':
            opt[i] = "DEF";
            break;
        case '4':
            opt[i] = "GHI";
            break;
        case '5':
            opt[i] = "JKL";
            break;
        case '6':
            opt[i] = "MNO";
            break;
        case '7':
            opt[i] = "PRS";
            break;
        case '8':
            opt[i] = "TUV";
            break;
        case '9':
            opt[i] = "WXY";
            break;
       }
    }
    int ret;
    for(int i = 0; i<4617; i++)
    {
        name >> inp;
        if(inp.length()==len)
        {
            ret = 1;
            for(int j = 0; j<len; j++)
            {
                if((opt[j].find(inp[j])<0)||(opt[j].find(inp[j])>2))
                {
                    ret = 0;
                }
            }
            if(ret==1)
            {
                if(counter!=0)
                {
                    outfile << endl;
                }
                outfile << inp;
                counter++;
            }
        }
    }
    if(counter==0)
    {
        outfile << "NONE";
    }
    outfile << endl;
    return 0;
}
