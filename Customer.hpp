#ifndef Customer_hpp
#define Customer_hpp

#include "Base.hpp"

class Customer {
/// Customer object, each representing a single customer with his "basket"
    amount objID;
    std::map<amount, amount> cart; // id of product, amount of product

public:
    Customer(amount argID);
    amount getID();
};

#endif /* Customer_hpp */
