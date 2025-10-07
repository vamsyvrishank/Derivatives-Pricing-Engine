#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "payoff.hpp"


//abstract base class

class Instrument {
    public:
        virtual ~Instrument() = default;
        virtual double payoff(double spot) const = 0;
        virtual double getMaturity() const = 0;
        virtual double getStrike() const = 0;
        virtual bool isCall() const = 0;

};

// concrete class
class EuropeanOption : public Instrument {
    PayOff* payoff_ptr;
    double T;
    public:
    EuropeanOption(const PayOff & p, double expiry) : payoff_ptr(p.clone()), T(expiry) {}
    ~EuropeanOption() { delete payoff_ptr; }
    double payoff(double spot) const  override {
      return (*payoff_ptr)(spot);
    }

    double getMaturity() const override {return T;}

    // helper functions to identify call/put type polymorphically
    bool isCall() const override { return dynamic_cast<const PayOffCall*>(payoff_ptr) != nullptr; }
    double getStrike() const override {
        if (auto call = dynamic_cast<const PayOffCall*>(payoff_ptr)) return call->getStrike();
        if (auto put = dynamic_cast<const PayOffPut*>(payoff_ptr)) return put->getStrike();
        return 0.0;
    }

};
#endif