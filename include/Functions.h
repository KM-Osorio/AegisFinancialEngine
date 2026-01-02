//
// Created by HP SUPPORT on 30/12/2025.
//

#ifndef PRUEBITA_FUNCTIONS_H
#define PRUEBITA_FUNCTIONS_H

std::ofstream output(const char *name) ;
std::ifstream input(const char *name) ;
std::vector <Candle> readData(const char*name);

Candle processData(std::string_view line);
std::string_view cleanData(std::string_view &line) ;
int cinDate(std::string_view line) ;
double cinPrice(std::string_view line);
double cinVolume(std::string_view line);
double cinChange(std::string_view line);
std::string_view tokenize(std::string_view &line,char c);

std::vector <UserData> loadUsers(const char*name);
UserData processUsers(std::string_view line);


std::vector <std::unique_ptr<Wallet>> loadWallets(const std::vector <UserData>&users);
void processWallets(std::vector <std::unique_ptr<Wallet>> &wallets,std::vector<Candle>&candles);
void makeExchanges(std::vector <Candle>&candles,Wallet &wallet);
std::unique_ptr<Wallet> loadWallet(const UserData user);
void MonthlyReport(const char*path,std::vector <std::unique_ptr<Wallet>> wallets);

void  title(std::ofstream &out);
void lines(std::ofstream &out,int n,char c);
#endif //PRUEBITA_FUNCTIONS_H