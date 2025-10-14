#ifndef STOCHASTICPROCESS_H
#define STOCHASTICPROCESS_H
#include <cmath>

using namespace std;

//abstract base class, all processes must inherit from this.

class StochasticProcess {
  public:
    virtual ~StochasticProcess() = default;


    // mu(S,t)
    //  drift
    virtual double drift( double S , double t) const = 0;

    // sigma(s, t) diffusion
    virtual double diffusion( double S , double t) const = 0;

    // step wise evolution - S0 , dt and dW
    virtual double evolve(double t, double S , double dt , double dW ) const = 0;
};



class BlackScholesProcess : public StochasticProcess {
  private:
    double mu_;
    double sigma_;
    double S0_;

  public:
    BlackScholesProcess(double S0, double mu, double sigma)
        : mu_(mu), sigma_(sigma), S0_(S0) {}

    double drift(double t, double S) const override {
      return mu_ * S;
    }

    double diffusion(double t, double S) const override {
      return sigma_ * S;
    }

    double evolve(double t, double S, double dt, double dW) const override {
      return S * exp((mu_ - 0.5 * sigma_ * sigma_) * dt + sigma_ * dW);
    }

    double initialValue() const { return S0_; }
  };


#endif