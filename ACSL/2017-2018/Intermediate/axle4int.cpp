//Aditya Sundaram
//4/12/18
//Kubik
//Contest 4
//Inter 5
//Enloe Magnet HS
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    ifstream infile("axleint.txt");
    string r = "ABDCDEFGHIJKLMNOPQRSTUVWXYZ";
    int c[26];
    int co = 0;
    string h[26];
    string command, input;
    string letter;
    int i2;
    for(int i = 0; i<26; i++)
    {
        c[i] = 0;
    }
    while(infile.good())//co<5
    {
        infile >> command;
        if(command=="RESET")
        {
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
            letter = "";
            for(int i = 0; i<26; i++)
            {
                h[i] = "";
                c[i] = 0;
            }
            for(int i = 0; i<input.length(); i++)
            {
                if(c[r.find(input[i])]==0)
                {
                    c[r.find(input[i])]++;
                    int place;
                    if(letter.length()==0)
                    {
                        letter = input.substr(i,1);
                        place = 0;
                    }
                    else if(input[i]>letter[letter.length()-1])
                    {
                        letter = letter + input.substr(i,1);
                        place = letter.length()-1;
                    }
                    else if(input[i]<letter[0])
                    {
                        letter = input.substr(i,1)+letter;
                        place = 0;
                    }
                    else
                    {
                        for(int j = 0; j<letter.length()-1; j++)
                        {
                            if((letter[j]<input[i])&&(letter[j+1]>input[i]))
                            {
                                letter.insert(j+1,input.substr(i,1));
                                place = j+1;
                                break;
                            }
                        }
                    }
                    for(int j = place; j<letter.length(); j++)
                    {
                        h[j] = h[j] + letter.substr(j,1);
                    }
                }
                else
                {
                    c[r.find(input[i])]++;
                }
            }
        }
        else if(command=="REPORT")
        {
            co++;
            infile >> i2;
            cout << h[i2-1] << endl;
        }
        else if(command=="ADD")
        {
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
            for(int i = 0; i<input.length(); i++)
            {
                if(c[r.find(input[i])]==0)
                {
                    c[r.find(input[i])]++;
                    int place;
                    if(letter.length()==0)
                    {
                        letter = input.substr(i,1);
                        place = 0;
                    }
                    else if(input[i]>letter[letter.length()-1])
                    {
                        letter = letter + input.substr(i,1);
                        place = letter.length()-1;
                    }
                    else if(input[i]<letter[0])
                    {
                        letter = input.substr(i,1)+letter;
                        place = 0;
                    }
                    else
                    {
                        for(int j = 0; j<letter.length()-1; j++)
                        {
                            if((letter[j]<input[i])&&(letter[j+1]>input[i]))
                            {
                                letter.insert(j+1,input.substr(i,1));
                                place = j+1;
                                break;
                            }
                        }
                    }
                    for(int j = place; j<letter.length(); j++)
                    {
                        h[j] = h[j] + letter.substr(j,1);
                    }
                }
                else
                {
                    c[r.find(input[i])]++;
                }
            }
        }
        else if(command=="DELETE")
        {
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
            for(int i = 0; i<input.length(); i++)
            {
                if(c[r.find(input[i])]==1)
                {
                    c[r.find(input[i])]--;
                    int place;
                    for(int j = 0; j<letter.length(); j++)
                    {
                        if(letter[j]==input[i])
                        {
                            place = j;
                            letter.erase(j,1);
                            break;
                        }
                    }
                    for(int j = place; j<letter.length(); j++)
                    {
                        h[j] = h[j]+letter.substr(j,1);
                    }
                }
                else
                {
                    c[r.find(input[i])]--;
                }
            }
        }
    }
}
