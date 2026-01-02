//
// Created by HP SUPPORT on 30/12/2025.
//

#include "../include/Utils.h"

using namespace std;
bool Wallet::executeBuy(double curentPrice) {
    if (curentPrice>0) {
        if (hasFound()) {
            double BTCquant=m_USD/(curentPrice*(1+m_comisionRate));
            monthlyRevenue+=curentPrice*m_comisionRate*BTCquant;
            m_USD=0;
            m_BTC+=BTCquant;
            // cout << "Successful transaction \n "
            //        "USD: "<< m_USD << "\n"
            //        " BTC: "<< m_BTC << endl;
            monthlyTransactions++;

            return true;
        }
    }
    // cout<<"invalid input"<<endl;
    return false;
}
bool Wallet::executeSell(double curentPrice) {
    if (curentPrice>0) {
        if (hasPosition()) {
            monthlyRevenue+=curentPrice*m_comisionRate*m_BTC;
            m_USD+=curentPrice*(1-m_comisionRate)*m_BTC;
            m_BTC=0;
            // cout << "Successful transaction \n "
            //        "USD: "<< m_USD << "\n"
            //        " BTC: "<< m_BTC << endl;

            monthlyTransactions++;
            return true;
        }
    }
    // cout<<"invalid input"<<endl;
    return false;
}


bool Wallet:: hasFound() const {
    if (m_USD>=1) return true;
    else return false;
}
bool Wallet:: hasPosition()const {
    if (m_BTC>0) return true;
    else return false;
}
void Wallet:: calculateTotalValue(double currentPrice){
    m_FinalCapital= m_USD + (m_BTC * currentPrice);
}
void Wallet:: calculateROI() {
    ROI=(m_FinalCapital-m_initialCapital)/m_initialCapital*100;
}
string Wallet::getName() const {
    return m_name;
}
double Wallet::getROI()const {
    return ROI;
}
double Wallet::getFinalBalance()const {
    return m_FinalCapital;
}
int Wallet::getMonthlyTransactions()const {
    return monthlyTransactions;
}
double Wallet::getInitialBalance()const {
    return m_initialCapital;
}
double Wallet::getMonthlyRevenue()const {
    return monthlyRevenue;
}

