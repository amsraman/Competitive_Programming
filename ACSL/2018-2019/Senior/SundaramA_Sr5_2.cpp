#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("sr2.txt");
    for(int z = 0; z<5; z++)
    {
        string in1, in2, in11, in22, r1, r2, ans;
        vector<int> sp;
        if(z!=0) getline(fin,in1);
        getline(fin,in1);
        getline(fin,in2);
        in11 = in1, in22 = in2;
        sp.push_back(-1);
        for(int i = 0; i<in1.length(); i++)
        {
            if(in1[i]==' ') sp.push_back(i);
        }
        sp.push_back(in1.length());
        for(int i = 0; i<sp.size()-1; i++)
        {
            string word = in1.substr(sp[i]+1,sp[i+1]-sp[i]-1);
            if((in22.find(word)>=0)&&(in22.find(word)<in22.length()))
            {
                in22.erase(in22.find(word),word.length());
                r1+=word;
            }
        }
        sp.clear();
        sp.push_back(-1);
        for(int i = 0; i<in2.length(); i++)
        {
            if(in2[i]==' ') sp.push_back(i);
        }
        sp.push_back(in2.length());
        for(int i = 0; i<sp.size()-1; i++)
        {
            string word = in2.substr(sp[i]+1,sp[i+1]-sp[i]-1);
            if((in11.find(word)>=0)&&(in11.find(word)<in11.length()))
            {
                in11.erase(in11.find(word),word.length());
                r2+=word;
            }
        }
        sp.clear();
        int p = 0;
        for(int i = 0; i<r1.length(); i++)
        {
            for(int j = p; j<r2.length(); j++)
            {
                if(r2[j]==r1[i])
                {
                    ans+=r1[i];
                    p = j+1;
                    break;
                }
            }
        }
        cout << ((ans.length()==0)?("NONE"):(ans)) << endl;
    }
}
