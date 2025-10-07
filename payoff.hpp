
#ifndef PAYOFF_H
#define PAYOFF_H

#include <algorithm>


// base class

class PayOff { 
    public : 
        PayOff() {}
        virtual ~PayOff() {}
        virtual double operator()(double spot ) const = 0 ; // pure virtual func
        virtual PayOff* clone() const = 0;


};

// PayOffCall

class PayOffCall : public PayOff {
    private : 
        double strike;

    public :
        PayOffCall(double K) : strike(K) {}
        virtual ~PayOffCall() {}

        virtual double operator()(double spot) const override {
            return std:: max(spot - strike , 0.0);
        }

        virtual PayOff* clone() const override {
            return new PayOffCall(*this);
        }
        double getStrike() const {return strike;}
};


// PayOffPut

class PayOffPut : public PayOff {
    private :
        double strike;

    public :
        PayOffPut(double K) : strike(K) {}
        virtual ~PayOffPut() {}
        virtual double operator()(double spot) const override {
            return std::max(strike - spot , 0.0);
        }
        virtual PayOff* clone() const override {
            return new PayOffPut(*this);
        }
    double getStrike() const { return strike; }
};

#endif