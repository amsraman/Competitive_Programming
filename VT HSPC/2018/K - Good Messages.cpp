#include <bits/stdc++.h>

using namespace std;

int o, n, g, b;
string message, vowels = "aeiouy";

int main()
{
    cin >> o >> message >> n;
    for(int i = 0; i<n; i++)
    {
        int c = 0, v = 0;
        for(int j = 0; j<message.length(); j++)
        {
            message[j] = ('a'+(message[j]-'a'+o)%26);
            c++;
            for(int k = 0; k<6; k++) if(message[j]==vowels[k]) c--, v++;
        }
        if(c>2*v) g++;
        else b++;
    }
    cout << ((g>b)?("Boris"):("Colleague")) << endl;
}
