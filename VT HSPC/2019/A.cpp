//Code by William Zhang
#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> x;
    long long sum=0;
    for(int i=0; i<n; i++){
        int num;
        cin>>num;
        sum+=num;
        x.push_back(sum);
    }
    if(sum%3!=0){
        cout<<-1;
    }
    else{
        int j=0;
        int bus1=x[j];
        while(bus1<sum/3){
            j++;
            bus1=x[j];
        }
        int k=j+1;
        int bus2=x[k];
        while(bus2<2*(sum/3)){
            k++;
            bus2=x[k];
        }
        if(bus1==sum/3&&bus2==2*sum/3&&2*bus1==bus2&&bus1*3==sum){
            cout<<j+1<<" "<<k+1;
        }
        else{
            cout<<-1;
        }
    }
}
