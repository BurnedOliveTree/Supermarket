//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Invoice_hpp
#define Invoice_hpp

#include "Consumer.hpp"
#include "Product.hpp"

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

class Invoice {
    bool isPayed;
    time_t date;
    int number;
    Consumer buyer;
    Consumer seller;
    map<unsigned short, unsigned short> products;
    vector<Product> *stock;
        
public:
    /**
     Invoice object constructor:
     @param argIsPayed Bool whether the invoice has been payed.
     @param argDate Type time_t specifies invoice date.
     @param argNumber Integer to numerate invoices.
     @param argBuyer Class Consumer object.
     @param argSeller Class Consumer object.
     @param argProducts Map containing product ID and quantity (both unsigned short type).
     */
    Invoice(bool argIsPayed = false, time_t argDate = 0, int argNumber = 0, Consumer argBuyer = 0, Consumer argSeller = 0, map<unsigned short, unsigned short> argProducts = map<unsigned short, unsigned short>());
    
    void editInvoice(bool argIsPayed, time_t argDate, int argNumber, Consumer argBuyer, Consumer argSeller, map<unsigned short, unsigned short> argProducts);
    
    // Operators overloading:
    /*bool operator==(Invoice other);
    bool operator!=(Invoice other);
    Invoice operator=(Invoice other);
    Invoice(Invoice &pattern);*/
    
    // Getters:
    bool getIsPayed();
    time_t getDate();
    int getNumber();
    Consumer getBuyer();
    Consumer getSeller();
    map<unsigned short, unsigned short> getProducts();

    // Setters:
    /**
     Sets isPayed attribute to given argument.
     @param newStatus New status of the payment.
     */
    void setIsPayed(bool newStatus);
    
    /**
     Sets date attribute to given argument.
     @param newDate New date of invoice.
     */
    void setDate(time_t newDate);
    
    /**
     Sets buyer attribute to given argument.
     @param newBuyer New buyer object.
     */
    void setBuyer(Consumer newBuyer);
    
    /**
     Sets seller attribute to given argument.
     @param newSeller New seller object.
    */
    void setSeller(Consumer newSeller);
    
    /**
     Sets number attribute to given argument.
     @param newNumber New number.
     */
    void setNumber(int newNumber);
    
    /**
     Sets stock.
     @param argStock Pointer to stock.
     */
    void setStock(vector<Product> *argStock);
    
    /**
     Replaces all the existing products with the new ones.
     @param newProducts New products map.
     */
    void setProducts(map<unsigned short, unsigned short> newProducts);
    

    // Tools to edit products:
    /**
     Adds product to the invoice. If already exist will stack with prevoiusy added.
     @param newProductID New product ID.
     @param newQuantity Quantity of the ne product.
     */
    void addProduct(unsigned short newProductID, unsigned short newQuantity);
    
    /**
     Removes specified product from the invoice (if exist).
     */
    void removeProduct(unsigned short newProductID, unsigned short newQuantity);
    
    // Additional features:
    /**
     Generates ASCII representation of the invoice.
     */
    string generate();
    
    /**
     Saves ASCII representation of the invoice to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    void save(string filename);
};

#endif /* Invoice_hpp */
