#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "payoff.hpp"

using namespace  std;
//abstract base class

class Instrument {
    public:

        virtual ~Instrument() = default;
        virtual double payoff(double spot) const = 0;
        virtual double payoff(const vector<double>& path) const = 0;
        virtual double getMaturity() const = 0;
        virtual double getStrike() const = 0;
        virtual bool isCall() const = 0;
        virtual bool isAmerican() const { return false; }

};

// concrete class
class EuropeanOption : public Instrument {

    PayOff* payoff_ptr;
    double T;

    public:
        EuropeanOption(const PayOff & p, const double expiry) : payoff_ptr(p.clone()), T(expiry) {}

        ~EuropeanOption() override { delete payoff_ptr; }

        double payoff(const double spot) const override
        {
          return (*payoff_ptr)(spot);
        }
    double payoff(const vector<double>& path) const override {
            return (*payoff_ptr)(path.back());
        }

    double getMaturity() const override {return T;}

    // helper functions to identify call/put type

    bool isCall() const override { return dynamic_cast<const PayOffCall*>(payoff_ptr) != nullptr; }
    bool isAmerican() const override { return false; }
    double getStrike() const override {
        if (const auto call = dynamic_cast<const PayOffCall*>(payoff_ptr)) return call->getStrike();
        if (const auto put = dynamic_cast<const PayOffPut*>(payoff_ptr)) return put->getStrike();
        return 0.0;
    }
};

class AmericanOption : public Instrument {
    PayOff* payoff_ptr;
    double T;

public:
    AmericanOption(const PayOff & p, const double expiry) : payoff_ptr(p.clone()), T(expiry) {}
    bool isAmerican() const override { return true; }
    ~AmericanOption() override { delete payoff_ptr; }

    double payoff(const double spot) const override
    {
        return (*payoff_ptr)(spot);
    }

    double payoff(const std::vector<double>& path) const override {
        return (*payoff_ptr)(path.back());
    }

    double getMaturity() const override {return T;}
    bool isCall() const override { return dynamic_cast<const PayOffCall*>(payoff_ptr) != nullptr; }

    double getStrike() const override {
        if (const auto call = dynamic_cast<const PayOffCall*>(payoff_ptr)) return call->getStrike();
        if (const auto put = dynamic_cast<const PayOffPut*>(payoff_ptr)) return put->getStrike();
        return 0.0;
    }
};




#endif