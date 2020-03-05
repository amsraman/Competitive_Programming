//Aditya Sundaram
//4/12/18
//Kubik
//Contest 4
//Senior 5
//Enloe Magnet HS
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string r = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ifstream infile("axlesenior.txt");
    string input;
    int c[26];
    int node[26];
    char no[26][2];
    for(int fj = 0; fj<5; fj++)
    {
        bool ex[26][2] = {false};
        for(int i = 0; i<26; i++)
        {
            node[i] = 0;
            c[i] = 0;
        }
        getline(infile,input);
        for(int i = 0; i<input.length(); i++)
        {
            if(input[i]==' ')
            {
                input.erase(i,1);
            }
        }
        for(int i = 0; i<input.length(); i++)
        {
            input[i] = char(toupper(input[i]));
        }
        char b = input[0];
        c[r.find(input[0])]++;
        for(int i = 1; i<input.length(); i++)
        {
            if(c[r.find(input[i])]>0)
            {
                c[r.find(input[i])]++;
            }
            else
            {
                b = input[0];
                bool done = true;
                while(done)
                {
                    if(input[i]>b)
                    {
                        if(ex[r.find(b)][1]==false)
                        {
                            done = false;
                        }
                        else
                        {
                            b = r[no[r.find(b)][1]];
                        }
                    }
                    else if(input[i]<b)
                    {
                        if(ex[r.find(b)][0]==false)
                        {
                            done = false;
                        }
                        else
                        {
                            b = r[no[r.find(b)][0]];
                        }
                    }
                }
                if(input[i]>b)
                {
                    ex[r.find(b)][1] = true;
                    no[r.find(b)][1] = r.find(input[i]);
                }
                else if(input[i]<b)
                {
                    ex[r.find(b)][0] = true;
                    no[r.find(b)][0] = r.find(input[i]);
                }
                node[r.find(b)]++;
                c[r.find(input[i])]++;
            }
        }
        int ans = 0;
        for(int i = 0; i<26; i++)
        {
            if(node[i]==1)
            {
                ans = ans+c[i];
            }
        }
        cout << ans << endl;
    }
}
