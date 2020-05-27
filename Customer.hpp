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

class Customer {
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
    void editCustomer(unsigned short argID, bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry);
    
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
    map<unsigned short, unsigned short> getBasket() const;
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
    void setBasket(map<Product*, unsigned short> newBasket);
    void addToBasket(Product*, unsigned short quantity);
    void removeFromBasket(Product*, unsigned short quantity);
    void clearBasket();
    
    string getInfo();
};

#endif /* Customer_hpp */
