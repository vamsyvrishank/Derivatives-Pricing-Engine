
#include <iostream>
#include "payoff.hpp"
#include  "VanillaOption.hpp"
#include "Instrument.hpp"
#include "MarketData.hpp"
#include <cmath>


using namespace std;

#include <iostream>
#include "PricingEngine.hpp"

int main() {

    MarketData data{};
    data.spot = 100;
    data.rate = 0.05;
    data.vol = 0.2;
    data.dividend = 0.0;

    double K = 100;
    double T = 1.0;


    //payoff
    PayOffCall callPayoff(K);
    EuropeanOption callOption(callPayoff , T);

    // BS discrete process
    BlackScholesProcess BSProcess(data.spot , data.rate , data.vol);

    int nPaths = 1000;
    int nSteps = 1000;

    MonteCarloEngine engine(BSProcess , nPaths , nSteps);

    double mcCallPrice = engine.calculate(callOption , data);
    cout << "Monte Carlo Call Option price BS Discrete Process : " << mcCallPrice << endl;


    // BS Closed form price
    BlackScholesAnalyticEngine BSAnalyticsEngine;
    double bsAnalyticsCallPrice = BSAnalyticsEngine.calculate(callOption , data);

    cout << "BS Closed form Call Option Price : " << bsAnalyticsCallPrice << endl;


    PayOffCall callPayOff(K);
    AmericanOption amerCall(callPayoff , T);

    BinomialEngine BnEngine(300);
    double bnPrice = BnEngine.calculate(amerCall , data);

    cout << "Binomial American Option Price : " << bnPrice << endl;
    return 0;
}
