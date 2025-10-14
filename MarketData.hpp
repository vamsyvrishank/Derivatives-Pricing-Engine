#ifndef MARKETDATA_H
#define MARKETDATA_H


struct MarketData
{
    /* data */
    double spot;
    double rate;
    double vol;
    double dividend;


    //create a default constructor
    MarketData() = default;

    MarketData(double S , double r , double sigma , double q = 0.0) :
    spot(S) , rate(r) , vol(sigma) , dividend(q) {}
};

#endif


