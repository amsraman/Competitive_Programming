/*
ID: adityasund1
TASK: contact
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream infile("contact.in");
    ofstream outfile("contact.out");
    int a, b, n;
    string s = "", s1;
    set<pair<int,pair<int,int> > > freq;
    vector<int> lis;
    int co[8193][12] = {0}, cou = 0, cc, sc;
    string bin[8193][12];
    infile >> a >> b >> n;
    infile.ignore();
    while(infile.good())
    {
        getline(infile,s1);
        s+=s1;
    }
    for(int i = a; i<=b; i++)
    {
        int bc = 0;
        for(int j = 0; j<i-1; j++)
        {
            bc*=2;
            bc+=((s[j])-'0');
        }
        for(int j = i-1; j<s.length(); j++)
        {
            bc*=2;
            bc%=(1<<i);
            bc+=(s[j]-'0');
            if(co[bc][i-1]==0)
            {
                co[bc][i-1] = 1;
                bin[bc][i-1] = s.substr(j-i+1,i);
                lis.push_back(bc);
            }
            else
            {
                co[bc][i-1]++;
            }
        }
        while(lis.size()!=0)
        {
            freq.insert({-co[lis[lis.size()-1]][i-1],{i,lis[lis.size()-1]}});
            lis.pop_back();
        }
    }
    freq.insert({1,{0,0}});
    set<pair<int,pair<int,int> > >::iterator it = freq.begin();
    cc = -(*it).first;
    outfile << cc << endl;
    sc = 0;
    while(cou<n)
    {
        sc++;
        if((sc%6==1)&&(sc>1))
        {
            outfile << endl;
        }
        outfile << bin[(*it).second.second][(*it).second.first-1];
        it++;
        if((*it).first==1)
        {
            break;
        }
        if(-(*it).first!=cc)
        {
            cou++;
            sc = 0;
            if(cou!=n)
            {
                cc = -(*it).first;
                outfile << endl << cc << endl;
            }
        }
        else if((sc%6!=0)||(sc==0))
        {
            outfile << " ";
        }
    }
    outfile << endl;
}
