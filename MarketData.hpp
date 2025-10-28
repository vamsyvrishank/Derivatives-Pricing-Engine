#ifndef MARKETDATA_H
#define MARKETDATA_H


struct MarketData
{
    /* data */
    double spot{0.0};
    double rate{0.0};
    double vol{0.0};
    double dividend{0.0};


    //create a default constructor
    MarketData() = default;

    MarketData(double S , double r , double sigma , double q = 0.0) :
    spot(S) , rate(r) , vol(sigma) , dividend(q) {}
};

#endif


