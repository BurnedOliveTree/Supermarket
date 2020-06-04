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
    virtual unsigned short getID() const = 0;
    virtual Customer getBuyer() const = 0;
    virtual Customer getSeller() const = 0;

    // Setters:
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
     @param argID Integer to numerate bills.
     @param argBuyer Class Customer object.
     @param argSeller Class Customer object.
     */
    Bill(unsigned short argID = 0, Customer argBuyer = 0, Customer argSeller = Customer(true, 99999, "Supermarket", "5351638772", "Poziomkowa", "15A", "00-009", "Szczebrzeszyn", "Atlantyda"));
    
    
    // Getters:
    unsigned short getID() const;
    Customer getBuyer() const;
    Customer getSeller() const;

    // Setters:
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
