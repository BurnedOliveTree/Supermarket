//
//  Consumer.hpp
//  Zadanie 3
//
//  Created by Paweł Müller on 07/04/2020.
//

#ifndef Consumer_hpp
#define Consumer_hpp

#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

class Consumer {
    bool isBusiness;
    string name;
    string taxNumber;
    string street;
    string buildingNumber;
    string postcode;
    string city;
    string country;
    
    map<unsigned short, unsigned short> basket; // Consumer's basket. [productID: quantity]
    
public:
    /**
     Consumer object constructor.
     @param argIsBusiness Bool determining whether the consumer is provate or corporate.
     @param argName Name of consumer.
     @param argTaxNumber Tax number of the consumer.
     @param argStreet Consumer's street.
     @param argBuildingNumber Consumer's building number (and if needed flat number).
     @param argPostcode Consumer's postcode.
     @param argCity Consumer's city.
     @param argCountry Consumer's country.
     */
    Consumer(bool argIsBusiness = false, string argName = "None", string argTaxNumber = "0000000000", string argStreet = "None", string argBuildingNumber = "None", string argPostcode = "None", string argCity = "None", string argCountry = "None");
    void editConsumer(bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry);
    
    // Getters:
    bool getIsBusiness();
    string getName();
    string getTaxNumber();
    string getStreet();
    string getBuildingNumber();
    string getPostcode();
    string getCity();
    string getCountry();
    map<unsigned short, unsigned short> getBasket();
    
    //Setters:
    void setIsBusiness(bool newIsBusiness);
    void setName(string newName);
    void setTaxNumber(string newTaxNumber);
    void setStreet(string newStreet);
    void setBuildingNumber(string newBuildingNumber);
    void setPostcode(string newPostcode);
    void setCity(string newCity);
    void setCountry(string newCountry);
    
    // Tools to edit Basket:
    void setBasket(map<unsigned short, unsigned short> newBasket);
    void addToBasket(unsigned short productID, unsigned short quantity);
    void removeFromBasket(unsigned short productID, unsigned short quantity);
    void clearBasket();
    
    string getInfo();
};

#endif /* Consumer_hpp */
