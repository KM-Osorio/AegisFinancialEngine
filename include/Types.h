//
//
//

#ifndef PRUEBITA_TYPES_H
#define PRUEBITA_TYPES_H
struct Candle {
    int date;
    double close;
    double open;
    double high;
    double low;
    double volume;
    double changeRate;
};

struct UserData {
    int id;
    std::string name;
    double initialCapital;
    std::string category;
    UserData():initialCapital(0.0),id(0){}
};


#endif //PRUEBITA_TYPES_H