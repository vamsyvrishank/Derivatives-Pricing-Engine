
#include <iostream>
#include "payoff.hpp"
#include  "VanillaOption.hpp"

using namespace std;

int main(){

    PayOffCall payoffcall(100.0);
    PayOffPut payoffput(100.0);

    VanillaOption vanillacall(payoffcall , 1.0); // expiry = 1 year
    VanillaOption vanillaput(payoffput , 1.0) ;

    double Spot = 105.0;

    cout<<"Call payoff is : "<< vanillacall.OptionPayOff(Spot)<<endl;
    cout<<"Put payoff is  : "<< vanillaput.OptionPayOff(Spot)<<endl;



    return 0;
    
}