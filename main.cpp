
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
    MarketData mkt(105.0, 0.05, 0.2, 0.0);

    PayOffCall call(100.0);
    PayOffPut put(100.0);

    EuropeanOption callOpt(call, 1.0);
    EuropeanOption putOpt(put, 1.0);

    const BlackScholesAnalyticEngine engine;

    std::cout << "European Call Price: " << engine.calculate(callOpt, mkt) << std::endl;
    std::cout << "European Put Price : " << engine.calculate(putOpt, mkt) << std::endl;

    return 0;
}
