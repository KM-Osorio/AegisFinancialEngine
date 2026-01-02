//
// Created by HP SUPPORT on 31/12/2025.
//

#ifndef PRUEBITA_WALLET_H
#define PRUEBITA_WALLET_H
#include "Types.h"

class Wallet {
protected:
    double m_initialCapital;
    double m_USD;
    double m_BTC;
    std::string m_name;
    double m_comisionRate;
    double m_FinalCapital;
    double monthlyRevenue;
    int monthlyTransactions;
    double ROI;
public:
    Wallet(double USD,std::string name,double com):m_USD(USD),m_BTC(0.0),m_name(name),m_comisionRate(com),m_FinalCapital(0),m_initialCapital(USD),monthlyTransactions(0),ROI(0),monthlyRevenue(0){};
    virtual ~Wallet()=default;
    bool hasFound()const;
    bool hasPosition()const;
    bool executeBuy(double currentPrice);
    bool executeSell(double currentPrice);
    void calculateTotalValue(double currentPrice);
    void calculateROI();
    std::string getName()const;
    double getROI()const;
    double getFinalBalance()const;
    double getInitialBalance()const ;
    int getMonthlyTransactions()const;
    double getMonthlyRevenue()const ;

    virtual void printStatus(std::ofstream &out) const {

    }

};

class Premium : public Wallet {
public:
        Premium(double USD,std::string name):Wallet(USD,name,0.0005){};

        void printStatus(std::ofstream &out) const override {
            out<<std::setprecision(2)<<std::fixed<<std::left;
            out<<std::setw(4)<<" "<<std::setw(50)<<m_name<<std::setw(20)<<"Premium";
            out<<"$"<<std::setw(20)<<m_initialCapital;
            out<<"$"<<std::setw(20)<<m_FinalCapital;
                                  out<<std::setw(10)<<monthlyTransactions;
            out<<ROI<<std::setw(10)<<"%";
            out<<"$"<<monthlyRevenue<<std::endl;
        }
};
class Pro : public Wallet {
public:
    Pro(double USD,std::string name):Wallet(USD,name,0.0025){};
    void printStatus(std::ofstream &out) const override {
        out<<std::setprecision(2)<<std::fixed<<std::left;
        out<<std::setw(4)<<" "<<std::setw(50)<<m_name<<std::setw(20)<<"Pro";
        out<<"$"<<std::setw(20)<<m_initialCapital;
        out<<"$"<<std::setw(20)<<m_FinalCapital;
        out<<std::setw(10)<<monthlyTransactions;
        out<<ROI<<std::setw(10)<<"%";
        out<<"$"<<monthlyRevenue<<std::endl;
    }
};

class Standard : public Wallet {
public:
        Standard(double USD,std::string name):Wallet(USD,name,0.005){};
    void printStatus(std::ofstream &out) const override {
        out<<std::setprecision(2)<<std::fixed<<std::left;
        out<<std::setw(4)<<" "<<std::setw(50)<<m_name<<std::setw(20)<<"Standard";
        out<<"$"<<std::setw(20)<<m_initialCapital;
        out<<"$"<<std::setw(20)<<m_FinalCapital;
        out<<std::setw(10)<<monthlyTransactions;
        out<<ROI<<std::setw(10)<<"%";
        out<<"$"<<monthlyRevenue<<std::endl;
    }
};
#endif //PRUEBITA_WALLET_H