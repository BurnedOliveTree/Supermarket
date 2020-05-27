//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Customer.hpp"

using namespace std;

Customer::Customer(unsigned short argID, bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
    basket.clear();
    editCustomer(argID, argIsBusiness, argName, argTaxNumber, argStreet, argBuildingNumber, argPostcode, argCity, argCountry);
}
void Customer::editCustomer(unsigned short argID, bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
    ID = argID;
    isBusiness = argIsBusiness;
    name = argName;
    taxNumber = argTaxNumber;
    street = argStreet;
    buildingNumber = argBuildingNumber;
    postcode = argPostcode;
    city = argCity;
    country = argCountry;
}

// Getters:
unsigned short Customer::getID() const {
    return ID;
}
bool Customer::getIsBusiness() const {
    return isBusiness;
}
string Customer::getName() const {
    return name;
}
string Customer::getTaxNumber() const {
    return taxNumber;
}
string Customer::getStreet() const {
    return street;
}
string Customer::getBuildingNumber() const {
    return buildingNumber;
}
string Customer::getPostcode() const {
    return postcode;
}
string Customer::getCity() const {
    return city;
}
string Customer::getCountry() const {
    return country;
}
map<Product*, unsigned short> Customer::getBasket() const {
    return basket;
}
unsigned long Customer::getBasketSize() const {
    return basket.size();
}

//Setters:
void Customer::setID(unsigned short newID) {
    ID = newID;
    return;
}

void Customer::setIsBusiness(bool newIsBusiness) {
    isBusiness = newIsBusiness;
    return;
}

void Customer::setName(string newName) {
    name = newName;
    return;
}

void Customer::setTaxNumber(string newTaxNumber) {
    taxNumber = newTaxNumber;
    return;
}

void Customer::setStreet(string newStreet) {
    street = newStreet;
    return;
}

void Customer::setBuildingNumber(string newBuildingNumber) {
    buildingNumber = newBuildingNumber;
    return;
}

void Customer::setPostcode(string newPostcode) {
    postcode = newPostcode;
    return;
}

void Customer::setCity(string newCity) {
    city = newCity;
    return;
}

void Customer::setCountry(string newCountry) {
    country = newCountry;
    return;
}


// Tools to edit Basket:
void Customer::setBasket(map<Product*, unsigned short> newBasket) {
    basket = newBasket;
    return;
}

void Customer::addToBasket(Product* argProduct, unsigned short argQuantity) {
    if (basket.find(argProduct) == basket.end())
        basket.insert(std::pair<Product*, unsigned short>(argProduct, argQuantity));
    else
        basket[argProduct] += argQuantity;
    argProduct -> decQuantity(argQuantity);
}

void Customer::removeFromBasket(Product* argProduct, unsigned short argQuantity) {
    basket.erase(argProduct);
    argProduct -> addQuantity(argQuantity);
    return;
}

void Customer::clearBasket() {
    basket.clear();
    return;
}

string Customer::getInfo() {
    if (isBusiness) return "Business client\n" + getName() + "\nTax no: " + getTaxNumber() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
    else return getName() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
}
