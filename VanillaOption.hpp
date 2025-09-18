#ifndef VANILLAOPTION_H
#define VANILLAOPTION_H

#include "payoff.hpp"

class VanillaOption {
    private:
        PayOff *payoff; // pointer to base class
        double expiry;
    
    public:
        VanillaOption(const PayOff &payoffObj , double T) {
            expiry = T;
            payoff = payoffObj.clone();
        };

        ~VanillaOption() {
            delete payoff;
        }

        double getExpiry() const {
            return expiry;
        }

        double OptionPayOff(double Spot){
            return (*payoff)(Spot);
        }
};

#endif

