//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Bill_hpp
#define Bill_hpp

#include "Customer.hpp"
#include "Product.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

class Bill {
protected:
    chrono::time_point<chrono::high_resolution_clock> date;
    unsigned short ID;
    Customer buyer;
    Customer seller;
        
public:
    /**
     Bill object constructor:
     @param argDate Type time_t specifies bill date.
     @param argID Integer to numerate bills.
     @param argBuyer Class Customer object.
     @param argSeller Class Customer object.
     */
    Bill(chrono::time_point<chrono::high_resolution_clock> argDate = chrono::steady_clock::now(), unsigned short argID = 0, Customer argBuyer = 0, Customer argSeller = 0);
    
    
    // Getters:
    chrono::time_point<chrono::high_resolution_clock> getDate() const;
    unsigned short getID() const;
    Customer getBuyer() const;
    Customer getSeller() const;

    // Setters:
    /**
     Sets date attribute to given argument.
     @param newDate New date of bill.
     */
    void setDate(chrono::time_point<chrono::high_resolution_clock> newDate);
    
    /**
     Sets buyer attribute to given argument.
     @param newBuyer New buyer object.
     */
    void setBuyer(Customer newBuyer);
    
    /**
     Sets seller attribute to given argument.
     @param newSeller New seller object.
    */
    void setSeller(Customer newSeller);
    
    /**
     Sets number attribute to given argument.
     @param newID New number.
     */
    void setID(unsigned short newID);
    
    /**
     Converts price in PLN/100 to PLN.
     @param price Price in PLN/100.
     */
    string convertPricePLN(unsigned short price) const;
    
    /**
     Converts g to kg.
     @param quantity Quantity in g.
     */
    string convertToKg(unsigned short quantity) const;
    
    /**
     Saves ASCII representation of the bill to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    void save(string filename);
    
    virtual string generate() const = 0;
};




class Invoice: public Bill {
    public:
    using Bill::Bill;
    
    /**
     Generates ASCII representation of the bill.
     */
    string generate() const;
};




class Receipt: public Bill {
    public:
    using Bill::Bill;
    
    /**
     Generates ASCII representation of the bill.
     */
    string generate() const;
};

#endif /* Bill_hpp */
