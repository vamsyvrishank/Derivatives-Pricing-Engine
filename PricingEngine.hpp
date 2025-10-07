#ifndef PRICINGENGINE_H
#define PRICINGENGINE_H

#include "Instrument.hpp"
#include "MarketData.hpp"
#include <cmath>

inline double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

class PricingEngine {
public:
    virtual ~PricingEngine() = default;
    virtual double calculate(const Instrument& inst, const MarketData& mkt) const = 0;
};

class BlackScholesAnalyticEngine : public PricingEngine {
public:
    double calculate(const Instrument& inst, const MarketData& mkt) const override {
        double S = mkt.spot;
        double r = mkt.rate;
        double sigma = mkt.vol;
        double q = mkt.dividend;
        double K = inst.getStrike();
        double T = inst.getMaturity();

        double d1 = (std::log(S / K) + (r - q + 0.5 * sigma * sigma) * T) /
                    (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if (inst.isCall())
            return S * std::exp(-q * T) * norm_cdf(d1) -
                   K * std::exp(-r * T) * norm_cdf(d2);
        else
            return K * std::exp(-r * T) * norm_cdf(-d2) -
                   S * std::exp(-q * T) * norm_cdf(-d1);
    }
};

#endif
