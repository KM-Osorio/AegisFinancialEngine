#include "Utils.h"

using namespace std;

int main() {

    vector <unique_ptr<Wallet>> wallets;

    vector<Candle>candles = readData("../data/Bitcoin Historical Data.csv");
    vector<UserData>users = loadUsers("../data/Users.cvs");
    wallets=loadWallets(users);
    processWallets(wallets,candles);
    MonthlyReport("../outputFiles/monthlyReport.txt",move(wallets));


    return 0;
}

