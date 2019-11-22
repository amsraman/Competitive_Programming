#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("cowcode.in");
    ofstream outfile("cowcode.out");
    long long n;
    string s;
    infile >> s >> n;
    n--;
    long long co = s.length();
    while(co*2<n)
    {
        co*=2;
    }
    while(co>=s.length())
    {
        n = ((n%co)-(n/co))%co;
        if(n<0){n+=co;}
        co/=2;
    }
    outfile << s[n] << endl;
}
