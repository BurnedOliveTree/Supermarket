//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Customer_hpp
#define Customer_hpp

#include "Product.hpp"

#include <string>
#include <map>

using namespace std;

class CustomerInterface {
public:
    // Getters:
    virtual unsigned short getID() const = 0;
    virtual bool getIsBusiness() const = 0;
    virtual string getName() const = 0;
    virtual string getTaxNumber() const = 0;
    virtual string getStreet() const = 0;
    virtual string getBuildingNumber() const = 0;
    virtual string getPostcode() const = 0;
    virtual string getCity() const = 0;
    virtual string getCountry() const = 0;
    virtual map<Product*, unsigned short> getBasket() const = 0;
    virtual unsigned long getBasketSize() const = 0;
    
    //Setters:
    virtual void setID(unsigned short newID) = 0;
    virtual void setIsBusiness(bool newIsBusiness) = 0;
    virtual void setName(string newName) = 0;
    virtual void setTaxNumber(string newTaxNumber) = 0;
    virtual void setStreet(string newStreet) = 0;
    virtual void setBuildingNumber(string newBuildingNumber) = 0;
    virtual void setPostcode(string newPostcode) = 0;
    virtual void setCity(string newCity) = 0;
    virtual void setCountry(string newCountry) = 0;
    
    // Tools to edit Basket:
    virtual void addToBasket(Product*, unsigned short quantity) = 0;
    virtual void removeFromBasket(Product*, unsigned short quantity) = 0;
    virtual void clearBasket() = 0;
};

class Customer : public CustomerInterface {
    unsigned short ID;
    bool isBusiness;
    string name;
    string taxNumber;
    string street;
    string buildingNumber;
    string postcode;
    string city;
    string country;

    map<Product*, unsigned short> basket; // Customer's basket. [Product: quantity]
    
public:
    /**
     Customer object constructor.
     @param argID Customer's ID.
     @param argIsBusiness Bool determining whether the customer is provate or corporate.
     @param argName Name of customer.
     @param argTaxNumber Tax number of the customer.
     @param argStreet Customer's street.
     @param argBuildingNumber Customer's building number (and if needed flat number).
     @param argPostcode Customer's postcode.
     @param argCity Customer's city.
     @param argCountry Customer's country.
     */
    Customer(unsigned short argID = 0, bool argIsBusiness = false, string argName = "None", string argTaxNumber = "0000000000", string argStreet = "None", string argBuildingNumber = "None", string argPostcode = "None", string argCity = "None", string argCountry = "None");
    
    // Getters:
    unsigned short getID() const;
    bool getIsBusiness() const;
    string getName() const;
    string getTaxNumber() const;
    string getStreet() const;
    string getBuildingNumber() const;
    string getPostcode() const;
    string getCity() const;
    string getCountry() const;
    map<Product*, unsigned short> getBasket() const;
    unsigned long getBasketSize() const;
    
    //Setters:
    void setID(unsigned short newID);
    void setIsBusiness(bool newIsBusiness);
    void setName(string newName);
    void setTaxNumber(string newTaxNumber);
    void setStreet(string newStreet);
    void setBuildingNumber(string newBuildingNumber);
    void setPostcode(string newPostcode);
    void setCity(string newCity);
    void setCountry(string newCountry);
    
    // Tools to edit Basket:
    void addToBasket(Product*, unsigned short quantity);
    void removeFromBasket(Product*, unsigned short quantity);
    void clearBasket();
};

#endif /* Customer_hpp */
