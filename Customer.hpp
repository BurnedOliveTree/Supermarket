//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Customer_hpp
#define Customer_hpp

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
    
    map<unsigned short, unsigned short> basket; // Customer's basket. [productID: quantity]
    
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
    unsigned short getID();
    bool getIsBusiness();
    string getName();
    string getTaxNumber();
    string getStreet();
    string getBuildingNumber();
    string getPostcode();
    string getCity();
    string getCountry();
    map<unsigned short, unsigned short> getBasket();
    unsigned long getBasketSize();
    
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
    void setBasket(map<unsigned short, unsigned short> newBasket);
    void addToBasket(unsigned short productID, unsigned short quantity);
    void removeFromBasket(unsigned short productID, unsigned short quantity);
    void clearBasket();
    
    string getInfo();
};

#endif /* Customer_hpp */
