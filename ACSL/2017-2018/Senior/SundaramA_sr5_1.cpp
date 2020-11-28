#include <iostream>
#include <string>

using namespace std;

char medi(char a[])
{
    char temp;
    string reff = "23456789TJQKA";
    for(int i = 0; i<5; i++)
    {
        for(int j = i; j<5; j++)
        {
            if(reff.find(a[i])<reff.find(a[j]))
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    return a[2];
}

int mini(int a, int b)
{
    if(a<b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int maxi(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    string card = "23456789TJQKA";
    int value[13] = {2,3,4,5,6,7,8,0,-10,11,12,13,14};
    int oldp, p, n, counter, player;
    char ref1[5], ref2[5], p1[5], p2[5], d1[5], d2[5];
    cout << "Enter Player 1's Deck: " << endl;
    for(int i = 0; i<5; i++)
    {
        cin >> ref1[i];
    }
    cout << "Enter Player 2's Deck: " << endl;
    for(int i = 0; i<5; i++)
    {
        cin >> ref2[i];
    }
    for(int a = 0; a<5; a++)
    {
        for(int i = 0; i<5; i++)
        {
            p1[i] = ref1[i];
            p2[i] = ref2[i];
        }
        cout << "Enter initial point value: " << endl;
        cin >> p;
        cout << "Enter deck" << endl;
        for(int i = 0; i<5; i++)
        {
            cin >> d1[i];
            cin >> d2[i];
        }
        counter = 0;
        while(p<100)
        {
            if(counter<11)
            {
                oldp = p;
                p = p+value[card.find(medi(p1))];
                if((medi(p1)=='7')&&(p>99))
                {
                    p = p-6;
                }
                if((double(mini(p,oldp))<33.5)&&(double(maxi(p,oldp))>33.5))
                {
                    p = p+5;
                }
                else if((double(mini(p,oldp))<55.5)&&(double(maxi(p,oldp))>55.5))
                {
                    p = p+5;
                }
                else if((double(mini(p,oldp))<77.5)&&(double(maxi(p,oldp))>77.5))
                {
                    p = p+5;
                }
                if(counter<9)
                {
                    p1[2] = d1[counter/2];
                }
                counter++;
                if(p<100)
                {
                   oldp = p;
                   p = p+value[card.find(medi(p2))];
                   if((medi(p2)=='7')&&(p>99))
                   {
                       p = p-6;
                   }
                   if((double(mini(p,oldp))<33.5)&&(double(maxi(p,oldp))>33.5))
                   {
                       p = p+5;
                   }
                   else if((double(mini(p,oldp))<55.5)&&(double(maxi(p,oldp))>55.5))
                   {
                       p = p+5;
                   }
                   else if((double(mini(p,oldp))<77.5)&&(double(maxi(p,oldp))>77.5))
                   {
                       p = p+5;
                   }
                   if(counter<8)
                   {
                       p2[2] = d2[(counter-1)/2];
                   }
                   counter++;
                }
            }
        }
        if(p>99)
        {
            player = 2-((counter+1)%2);
            cout << p << ", Player #" << player << endl;
        }
    }
    return 0;
}
