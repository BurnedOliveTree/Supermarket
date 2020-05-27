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

class Product {
    string name; // A name of the product.
    unsigned short ID; // An identifier of the product.
    unsigned int price; // Price netto in 1/100 PLN (gr).
    unsigned short VAT; // VAT value (in percents).
    unsigned short quantity; // Quantity of the product in warehouse.
    unsigned short reservedQuantity; // Quantity of the product reserved for clients (not on shelf, not bought yet).
    
public:
    Product(string argName = "None", unsigned short argID = 0, unsigned int argPrice = 0, unsigned short argVAT = 0, unsigned short argQuantity = 0, unsigned short argReservedQuantity = 0);
    void editProduct(string argName, unsigned short argID, unsigned int argPrice, unsigned short argVAT, unsigned short argQuantity, unsigned short argReservedQuantity = 0);
        
    // Getters:
    string getName();
    unsigned short getID();
    unsigned int getPrice();
    unsigned short getVAT();
    unsigned short getQuantity();
    unsigned short getReservedQuantity();
    
    // Setters:
    void setName(string newName);
    void setID(unsigned short newID);
    void setPrice(unsigned int newPrice);
    void setVAT(unsigned short newVAT);
    void setQuantity(unsigned short newQuantity);
    void setReservedQuantity(unsigned short newReservedQuantity);
    
    // Additional features:
    string getInfo();
    int calculatePriceBrutto();
};

#endif /* Product_hpp */
