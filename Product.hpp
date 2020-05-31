//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Product_hpp
#define Product_hpp

#include <string>
#include <cmath>

using namespace std;

enum Measure{pcs, g};

class ProductInterface {
public:
    // Getters:
    virtual string getName() const = 0;
    virtual unsigned short getID() const = 0;
    virtual unsigned int getPrice() const = 0;
    virtual unsigned short getVAT() const = 0;
    virtual unsigned short getQuantity() const = 0;
    virtual Measure getMeasureUnits() const = 0;
    
    // Setters:
    virtual void setName(string newName) = 0;
    virtual void setID(unsigned short newID) = 0;
    virtual void setPrice(unsigned int newPrice) = 0;
    virtual void setVAT(unsigned short newVAT) = 0;
    virtual void setQuantity(unsigned short newQuantity) = 0;
    virtual void addQuantity(unsigned short argQuantity) = 0;
    virtual void decQuantity(unsigned short argQuantity) = 0;
    
    // Additional features:
    virtual int calculatePriceBrutto() = 0;
};

class Product : public ProductInterface {
    string name; // A name of the product.
    unsigned short ID; // An identifier of the product.
    unsigned int price; // Price netto in 1/100 PLN (gr).
    unsigned char VAT; // VAT value (in percents).
    unsigned short quantity; // Quantity of the product in warehouse.
    Measure measureUnits;
    
public:
    Product(string argName = "None", unsigned short argID = 0, unsigned int argPrice = 0, unsigned char argVAT = 0, unsigned short argQuantity = 0, Measure argMeasureUnits = pcs);
        
    // Getters:
    string getName() const;
    unsigned short getID() const;
    unsigned int getPrice() const;
    unsigned short getVAT() const;
    unsigned short getQuantity() const;
    Measure getMeasureUnits() const;
    
    // Setters:
    void setName(string newName);
    void setID(unsigned short newID);
    void setPrice(unsigned int newPrice);
    void setVAT(unsigned short newVAT);
    void setQuantity(unsigned short newQuantity);
    void addQuantity(unsigned short argQuantity);
    void decQuantity(unsigned short argQuantity);
    
    // Additional features:
    int calculatePriceBrutto();
};

#endif /* Product_hpp */
