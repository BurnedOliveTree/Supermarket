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

class BillInterface {
public:
    virtual chrono::time_point<chrono::high_resolution_clock> getDate() const = 0;
    virtual unsigned short getID() const = 0;
    virtual Customer getBuyer() const = 0;
    virtual Customer getSeller() const = 0;

    // Setters:
    /**
     Sets date attribute to given argument.
     @param newDate New date of bill.
     */
    virtual void setDate(chrono::time_point<chrono::high_resolution_clock> newDate) = 0;
    
    /**
     Sets buyer attribute to given argument.
     @param newBuyer New buyer object.
     */
    virtual void setBuyer(Customer newBuyer) = 0;
    
    /**
     Sets seller attribute to given argument.
     @param newSeller New seller object.
    */
    virtual void setSeller(Customer newSeller) = 0;
    
    /**
     Sets number attribute to given argument.
     @param newID New number.
     */
    virtual void setID(unsigned short newID) = 0;
    
    /**
     Saves ASCII representation of the bill to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    virtual void save(string filename) = 0;
};

class Bill : public BillInterface {
protected:
    chrono::time_point<chrono::high_resolution_clock> date;
    unsigned short ID;
    Customer buyer;
    Customer seller;
    
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
    
    virtual string generate() const = 0;
        
public:
    /**
     Bill object constructor:
     @param argDate Type time_t specifies bill date.
     @param argID Integer to numerate bills.
     @param argBuyer Class Customer object.
     @param argSeller Class Customer object.
     */
    Bill(unsigned short argID = 0, Customer argBuyer = 0, Customer argSeller = 0, chrono::time_point<chrono::high_resolution_clock> argDate = chrono::steady_clock::now());
    
    
    // Getters:
    chrono::time_point<chrono::high_resolution_clock> getDate() const;
    unsigned short getID() const;
    Customer getBuyer() const;
    Customer getSeller() const;

    // Setters:
    void setDate(chrono::time_point<chrono::high_resolution_clock> newDate);
    void setBuyer(Customer newBuyer);
    void setSeller(Customer newSeller);
    void setID(unsigned short newID);
    void save(string filename);
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
