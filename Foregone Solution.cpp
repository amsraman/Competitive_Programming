#include <iostream>

using namespace std;

int t, n;

int main()
{
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        int sp = 0;
        string in, a1, a2;
        cin >> in;
        if(in[0]==1) a1 = "1", sp++;
        for(int i = sp; i<in.length(); i++)
        {
            if(in[i]=='0') a1+='0', a2+='0';
            else if(in[i]=='5') a1+='3', a2+='2';
            else a1+=('0'+((in[i]-'0')-1)), a2+='1';
        }
        cout << "Case #" << z+1 << ": " << a1 << " " << a2 << endl;
    }
}
