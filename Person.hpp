//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Person_hpp
#define Person_hpp

#include "Product.hpp"

#include <string>
#include <map>

using namespace std;

class Person {
protected:
    unsigned short ID;
    string name;

public:
    Person(unsigned short argID = 0, string argName = "John Doe");
    unsigned short getID() const;
    string getName() const;
    void setID(unsigned short newID);
    void setName(string newName);
};





class Customer : public Person {
protected:
    map<Product*, unsigned short> basket;

public:
    Customer(unsigned short argID = 0, string argName = "John Doe");
    map<Product*, unsigned short> getBasket() const;
    unsigned long getBasketSize() const;
    
    // Tools to edit Basket:
    void addToBasket(Product*, unsigned short quantity);
    void removeFromBasket(Product*, unsigned short quantity);
    void clearBasket();
};





class BusinessCustomer : public Customer {
    unsigned short ID;
    string name;
    string taxNumber;
    string street;
    string buildingNumber;
    string postcode;
    string city;
    string country;

public:
    /**
     Customer object constructor.
     @param argID Customer's ID.
     @param argName Name of customer.
     @param argTaxNumber Tax number of the customer.
     @param argStreet Customer's street.
     @param argBuildingNumber Customer's building number (and if needed flat number).
     @param argPostcode Customer's postcode.
     @param argCity Customer's city.
     @param argCountry Customer's country.
     */
    BusinessCustomer(unsigned short argID = 0, string argName = "John Doe", string argTaxNumber = "0000000000", string argStreet = "None", string argBuildingNumber = "None", string argPostcode = "None", string argCity = "None", string argCountry = "None");
    
    // Getters:
    string getTaxNumber() const;
    string getStreet() const;
    string getBuildingNumber() const;
    string getPostcode() const;
    string getCity() const;
    string getCountry() const;

    //Setters:
    void setTaxNumber(string newTaxNumber);
    void setStreet(string newStreet);
    void setBuildingNumber(string newBuildingNumber);
    void setPostcode(string newPostcode);
    void setCity(string newCity);
    void setCountry(string newCountry);
};





class Employee : public Person {
    bool occupied;

public:
    Employee(unsigned short argID, std::string argName);
    bool isOccupied() const;
    void setFree();
    void setBusy();
};



/* class CustomerInterface {
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
};*/

#endif /* Person_hpp */
