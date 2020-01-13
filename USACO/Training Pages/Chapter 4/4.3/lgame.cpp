/*
ID: adityasund1
TASK: lgame
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ar[26] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7}, ans1;
string in, per;
vector<string> vdict;
vector<pair<string,string> > ans2;
bool chosen[7];

int points(string a, string b)
{
    int ret = 0;
    for(int i = 0; i<a.length(); i++){ret+=ar[a[i]-'a'];}
    for(int i = 0; i<b.length(); i++){ret+=ar[b[i]-'a'];}
    return ret;
}

bool bsearch(string a)
{
    int l = 0, g = vdict.size()-1;
    while(l<=g)
    {
        int mid = (l+g)/2;
        if(vdict[mid]==a){return true;}
        else if(vdict[mid]<a){l = mid+1;}
        else{g = mid-1;}
    }
    return false;
}

void permut(int a)
{
    if(a==0)
    {
        for(int i = 1; i<=in.length(); i++)
        {
            if(bsearch(per.substr(0,i)))
            {
                for(int j = i; j<=in.length(); j++)
                {
                    if((bsearch(per.substr(i,in.length()-j)))||(in.length()==j))
                    {
                        if(points(per.substr(0,i),per.substr(i,in.length()-j))>ans1)
                        {
                            while(ans2.size()!=0){ans2.pop_back();}
                            if(per.substr(0,i)<per.substr(i,in.length()-j)||(in.length()==j)){ans2.push_back({per.substr(0,i),per.substr(i,in.length()-j)});}
                            else{ans2.push_back({per.substr(i,in.length()-j),per.substr(0,i)});}
                        }
                        else if(points(per.substr(0,i),per.substr(i,in.length()-j))==ans1)
                        {
                            if(per.substr(0,i)<per.substr(i,in.length()-j)||(in.length()==j)){ans2.push_back({per.substr(0,i),per.substr(i,in.length()-j)});}
                            else{ans2.push_back({per.substr(i,in.length()-j),per.substr(0,i)});}
                        }
                        ans1 = max(ans1,points(per.substr(0,i),per.substr(i,in.length()-j)));
                    }
                }
            }
        }
        return;
    }
    for(int i = 0; i<in.length(); i++)
    {
        if(!chosen[i])
        {
            chosen[i] = true;
            per+=in.substr(i,1);
            permut(a-1);
            chosen[i] = false;
            per = per.substr(0,per.size()-1);
        }
    }
}

int main()
{
    ifstream infile("lgame.in");
    ifstream dict("lgame.dict");
    ofstream outfile("lgame.out");
    dict >> in;
    while(in!=".")
    {
        vdict.push_back(in);
        dict >> in;
    }
    infile >> in;
    permut(in.length());
    sort(ans2.begin(),ans2.end());
    outfile << ans1 << endl;
    for(int i = 0; i<ans2.size(); i++)
    {
        if((ans2[i-1]!=ans2[i])||(i==0))
        {
            outfile << ans2[i].first;
            if(ans2[i].second!="")
            {
                outfile << " " << ans2[i].second;
            }
            outfile << endl;
        }
    }
}
