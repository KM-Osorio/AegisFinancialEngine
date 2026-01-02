//
// Created by HP SUPPORT on 30/12/2025.
//


#define noFound -1
#include "Utils.h"
#include <memory>
using namespace std;
namespace fs=filesystem;

ifstream input(const char *name) {
    fs::path filePath(name);

    if (!fs::exists(filePath)) {
        cerr << "File " << name << " does not exist" << endl;
        cerr << "File absolute location " << fs::absolute(filePath)<< endl;
        cerr << "current location " << fs::current_path()<< endl;
        exit(1);
    }

    ifstream file(name,ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file " << name << endl;
        exit(1);
    }
    return file;

}
ofstream output(const char *name) {
    fs::path filePath(name);

    if (!fs::exists(filePath)) {
        cerr << "File " << name << " does not exist" << endl;
        cerr << "File absolute location " << fs::absolute(filePath)<< endl;
        cerr << "current location " << fs::current_path()<< endl;
        exit(1);
    }
    ofstream file(name,ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file " << name << endl;
        exit(1);
    }
    return file;

}
vector <Candle> readData(const char*name) {
    vector<Candle>candles;
    string line;
    ifstream in=input(name);
    getline(in,line);
    while (true) {
        getline(in,line);
        if (in.eof()) break;
        if (line.empty()) continue;
        candles.push_back(processData(line));
    }
    return candles;
}
Candle processData(string_view line) {
   Candle candle;
    candle.date=cinDate(cleanData(line));
    candle.close=cinPrice(cleanData(line));
    candle.open=cinPrice(cleanData(line));
    candle.high=cinPrice(cleanData(line));
    candle.low=cinPrice(cleanData(line));
    candle.volume=cinVolume(cleanData(line));
    candle.changeRate=cinChange(cleanData(line));
    line="";
    return candle;
}
double cinVolume(string_view line) {
    if (line.empty()) return 0.0;
    char unit=line.back();
    double multiplier = 1.0;
    if (unit == 'K') multiplier = 1000.0;
    else if (unit == 'M') multiplier = 1000000.0;
    else if (unit == 'B') multiplier = 1000000000.0;
    if (unit == 'K' || unit == 'M' || unit == 'B') {
        line.remove_suffix(1);
    }
    return stod(string(line)) * multiplier;
}
string_view cleanData(string_view &line) {
    if (line.empty()) return {};
    if (line.front()=='"')line.remove_prefix(1);
    string_view token=tokenize(line,'"');
    line.remove_prefix(1);
    return token;
}

int cinDate(string_view line) {
    if (line.empty()) return 0;
    string month=tokenize(line,'/').data();
    string day=tokenize(line,'/').data();
    string year=tokenize(line,'/').data();
    return stoi(year)*10000+stoi(month)*100+stoi(day);
}
double cinPrice(string_view line) {
    string price;
    for (int i=0;i<line.length();i++) if (line[i]!=',') price.push_back(line[i]);
    return (price.empty())?0.0 : stod(price);
}
string_view tokenize(string_view &line,char c) {
    if (line.empty()) return {};
    int end=line.find(c);
    if (end==string_view::npos) return line;
    string_view token=line.substr(0,end);
    line.remove_prefix(token.size()+1);
    return token;
}
double cinChange(std::string_view line) {
    int sign=1;
    if (line.at(0)=='-') {
        sign=-1;
        line.remove_prefix(1);
    }
    string change=tokenize(line,'%').data();
    return stod(change)*sign;
}

vector <UserData> loadUsers(const char*name) {
    ifstream in=input(name);
    string line;
    vector<UserData>users;
    while (true) {
        getline(in,line);
        if (in.eof())break;
        users.push_back(processUsers(line));
    }
    return users;
}

UserData processUsers(string_view line) {
    UserData user;
    user.id=stoi(tokenize(line,',').data());
    user.name=tokenize(line,',');
    user.initialCapital=stod(tokenize(line,',').data());
    user.category=tokenize(line,'\n').data();
    return user;
}

void makeExchanges(vector <Candle>&candles,Wallet &wallet) {
    double sum=0,medium=0;
    deque<double>window;
    for (auto &candle:candles) {
        sum+=candle.close;
        window.push_back(candle.close);
       if (window.size()>5) {
           sum-=window.front();
           window.pop_front();
           medium=sum/window.size();
           if (candle.close<medium) wallet.executeBuy(candle.close);
           if (candle.close > medium) wallet.executeSell(candle.close);
       }
    }
    wallet.calculateTotalValue(candles.back().close);
    wallet.calculateROI();
}

vector <unique_ptr<Wallet>> loadWallets(const vector <UserData>&users) {
    vector <unique_ptr<Wallet>>wallets;
    for (auto &user:users) {
        wallets.push_back(loadWallet(user));
    }
    return wallets;
}
unique_ptr<Wallet> loadWallet(const UserData user) {
    unique_ptr<Wallet>wallet;
    if (user.category=="Premium") {
        wallet= make_unique<Premium>(user.initialCapital,user.name);
    }else if (user.category=="Pro") {
        wallet= make_unique<Pro>(user.initialCapital,user.name);
    }else{
        wallet= make_unique<Standard>(user.initialCapital,user.name);
    }
    return wallet;
}

void processWallets(vector <unique_ptr<Wallet>> &wallets,vector<Candle>&candles) {
    for (auto &wallet : wallets) {
        makeExchanges(candles,*wallet);
    }
}

void MonthlyReport(const char*path,const vector <unique_ptr<Wallet>> wallets) {
    ofstream out=output(path);
    string name_highestROIUser;
    double finalBalances=0,initialBalances=0,highestROI,totalRevenue=0;
    int totalTransactions=0;
    title(out);
    for (int i=0;i<wallets.size();i++) {
        wallets[i]->printStatus(out);
        if (i==0) {
            name_highestROIUser=wallets[i]->getName();
            highestROI=wallets[i]->getROI();
        }else {
            if (wallets[i]->getROI()>highestROI) {
                name_highestROIUser=wallets[i]->getName();
                highestROI=wallets[i]->getROI();
            }
        }
        initialBalances+=wallets[i]->getInitialBalance();
        totalTransactions+=wallets[i]->getMonthlyTransactions();
        finalBalances+=wallets[i]->getFinalBalance();
        totalRevenue+=wallets[i]->getMonthlyRevenue();
    }
    lines(out,150,'-');
    out<<setw(74)<<' '<<"$"<<initialBalances<<setw(20)<<setw(10)<<' '<<"$"<<setw(20)<<finalBalances<<setw(24)<<totalTransactions<<"$"<<totalRevenue<<endl;
lines(out,150,'=');
    out<<setw(4)<<' '<<"METRIC ANALYSIS"<<endl;
    out<<setw(10)<<' '<<"• Total Monthly Revenue: $"<<totalRevenue<<" USD"<<endl;
    out<<setw(10)<<' '<<"• Total Operations: A total of "<<totalTransactions<<" buy/sell transactions were executed"<<endl;
    out<<setw(10)<<' '<<"• Top Performer: The user "<<name_highestROIUser<<" achieved the highest margin with "<<highestROI<<"%"<<endl;
    lines(out,150,'=');
}

void  title(ofstream &out) {
    lines(out,150,'=');
    out <<setw(80)<<"Performance Monthly Report"<<endl;
    lines(out,150,'=');
    out << std::left << std::setw(54) << "    USER"
         <<std::setw(20) << "CATEGORY"
         << std::setw(21) << "INITIAL BALANCE"
         << std::setw(21) << "FINAL BALANCE"
         << std::setw(11) << "OPS"
         << std::setw(10) << "ROI"
            <<"REVENUE"<<endl;
    lines(out,150,'=');
}
void lines(ofstream &out,int n,char c) {
    for (int i=0;i<n;i++) out << c;
    out << std::endl;
}