# Derivatives-Pricing-Engine
A modular high performance c++ derivatives pricing library that implements analytic, tree and monte carlo pricing for various payoffs. with object oriented design patterns ( Strategy , Factory , Decorator , Bridge )


Project Structure : 


PricingEngine
├── BlackScholesAnalyticEngine
├── MonteCarloEngine
├── BinomialEngine
└── FiniteDifferenceEngine

StochasticProcess
├── BlackScholesProcess
├── HestonProcess
└── SABRProcess

Instrument
├── EuropeanOption
├── AsianOption
└── BarrierOption


