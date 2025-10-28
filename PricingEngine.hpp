#ifndef PRICINGENGINE_H
#define PRICINGENGINE_H

#include "Instrument.hpp"
#include "MarketData.hpp"
#include "Instrument.hpp"
#include "MarketData.hpp"
#include "StochasticProcess.hpp"
#include <cmath>
#include <random>


using namespace std;

inline double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

class PricingEngine {
public:
    virtual ~PricingEngine() = default;
    virtual double calculate(const Instrument& inst, const MarketData& mkt) = 0;
};



class BlackScholesAnalyticEngine : public PricingEngine {
public:
    double calculate(const Instrument& inst, const MarketData& mkt) override {


        double S = mkt.spot;
        double r = mkt.rate;
        double sigma = mkt.vol;
        double q = mkt.dividend;
        double K = inst.getStrike();
        double T = inst.getMaturity();

        double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * T) /
                    (sigma * sqrt(T));
        double d2 = d1 - sigma * sqrt(T);

        cout<<"Calling the Black Scholes Pricing Method"<<endl;

        if (inst.isCall())
            return S * std::exp(-q * T) * norm_cdf(d1) -
                   K * std::exp(-r * T) * norm_cdf(d2);
        else
            return K * std::exp(-r * T) * norm_cdf(-d2) -
                   S * std::exp(-q * T) * norm_cdf(-d1);
    }
};

class MonteCarloEngine : public PricingEngine {
    private:
        const StochasticProcess &process;
        int  nPaths_;
        int  nSteps_;
        bool store_paths_;

    public:
    vector<vector<double>> paths_;
    MonteCarloEngine(const StochasticProcess &p , int nPaths , int nSteps , bool store_paths = false) : process(p) {
        nPaths_ = nPaths;
        nSteps_ = nSteps;
        store_paths_ = store_paths;
        if (store_paths) {
            paths_.resize(nPaths , vector<double>(nSteps+1));
        }
    }

    double calculate(const Instrument& inst, const MarketData& mkt) override {

        double S0 = mkt.spot;
        double r = mkt.rate;
        double T = inst.getMaturity();

        double dt = T / nSteps_;
        double discount = exp(-r*T);

        std::mt19937 rng(random_device{}());
        normal_distribution<> norm(0.0 , 1.0);

        double payoff_sum = 0.0;

        for (int i =0 ; i < nPaths_; i++) {

            vector<double> path(nSteps_ + 1 );
            path[0] = S0;
            double t = 0.0;

            for (int j=1 ; j<=nSteps_;j++) {
                double z = norm(rng);
                path[j] = process.evolve(t, path[j-1] , dt , sqrt(dt)*z);
                t += dt;
            }

            if (store_paths_) {
                paths_[i] = path;
            }

            double payoff = inst.payoff(path);
            payoff_sum += payoff;

        }

        return discount * (payoff_sum / nPaths_);

    }

    const std::vector<std::vector<double>>& getPaths() const {
        return paths_;
    }


};

class BinomialEngine : public PricingEngine {
private:
    int steps;

public:
    explicit BinomialEngine(int nSteps) : steps(nSteps) {}

    double calculate(const Instrument& inst, const MarketData& data) override {
        double T = inst.getMaturity();
        double dt = T / steps;
        double u = exp(data.vol * sqrt(dt));
        double d = 1.0 / u;
        double discountFactor = exp(-data.rate * dt);
        double p = (exp((data.rate - data.dividend) * dt) - d) / (u - d);

        // Spot prices at maturity
        vector<double> spotAtMaturity(steps + 1);
        for (int i = 0; i <= steps; i++) {
            spotAtMaturity[i] = data.spot * pow(u, steps - i) * pow(d, i);
        }

        // Option values at maturity
        vector<double> optionValues(steps + 1);
        for (int i = 0; i <= steps; i++) {
            optionValues[i] = inst.payoff(spotAtMaturity[i]);
        }

        // Backward induction
        for (int step = steps - 1; step >= 0; step--) {
            for (int i = 0; i <= step; i++) {
                double continuation = discountFactor * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);

                if (inst.isAmerican()) {
                    double spot = data.spot * pow(u, step - i) * pow(d, i);
                    double exercise = inst.payoff(spot);
                    optionValues[i] = max(continuation, exercise);
                } else {
                    optionValues[i] = continuation;
                }
            }
        }

        return optionValues[0];
    }
};

#endif
