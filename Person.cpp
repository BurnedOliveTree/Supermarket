//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Person.hpp"

using namespace std;

void Person::setID(unsigned short newID) {
    ID = newID;
    return;
}

void Person::setName(string newName) {
    name = newName;
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

map<Product*, unsigned short> Customer::getBasket() const {
    return basket;
}

unsigned long Customer::getBasketSize() const {
    return basket.size();
}





BusinessCustomer::BusinessCustomer(unsigned short argID, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
    basket.clear();
    ID = argID;
    name = argName;
    taxNumber = argTaxNumber;
    street = argStreet;
    buildingNumber = argBuildingNumber;
    postcode = argPostcode;
    city = argCity;
    country = argCountry;
}

// Getters:
unsigned short Person::getID() const {
    return ID;
}

string Person::getName() const {
    return name;
}

string BusinessCustomer::getTaxNumber() const {
    return taxNumber;
}

string BusinessCustomer::getStreet() const {
    return street;
}

string BusinessCustomer::getBuildingNumber() const {
    return buildingNumber;
}

string BusinessCustomer::getPostcode() const {
    return postcode;
}

string BusinessCustomer::getCity() const {
    return city;
}

string BusinessCustomer::getCountry() const {
    return country;
}





void BusinessCustomer::setTaxNumber(string newTaxNumber) {
    taxNumber = newTaxNumber;
    return;
}

void BusinessCustomer::setStreet(string newStreet) {
    street = newStreet;
    return;
}

void BusinessCustomer::setBuildingNumber(string newBuildingNumber) {
    buildingNumber = newBuildingNumber;
    return;
}

void BusinessCustomer::setPostcode(string newPostcode) {
    postcode = newPostcode;
    return;
}

void BusinessCustomer::setCity(string newCity) {
    city = newCity;
    return;
}

void BusinessCustomer::setCountry(string newCountry) {
    country = newCountry;
    return;
}






Employee::Employee(unsigned short argID, std::string argName) {
    ID = argID;
    name = argName;
    occupied = false;
}

bool Employee::isOccupied() const {
/// returns current status of this Employee
    return occupied;
};

void Employee::setFree() {
/// changes current status of this Employee into free
    occupied = false;
};

void Employee::setBusy() {
/// changes current status of this Employee into busy
    occupied = true;
};
