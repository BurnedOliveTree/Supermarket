//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Customer.hpp"

using namespace std;

Customer::Customer(bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
    basket.clear();
    editCustomer(argIsBusiness, argName, argTaxNumber, argStreet, argBuildingNumber, argPostcode, argCity, argCountry);
}
void Customer::editCustomer(bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
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
bool Customer::getIsBusiness() {
    return isBusiness;
}
string Customer::getName() {
    return name;
}
string Customer::getTaxNumber() {
    return taxNumber;
}
string Customer::getStreet() {
    return street;
}
string Customer::getBuildingNumber() {
    return buildingNumber;
}
string Customer::getPostcode() {
    return postcode;
}
string Customer::getCity() {
    return city;
}
string Customer::getCountry() {
    return country;
}
map<unsigned short, unsigned short> Customer::getBasket() {
    return basket;
}

//Setters:
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
void Customer::setBasket(map<unsigned short, unsigned short> newBasket) {
    basket = newBasket;
    return;
}

void Customer::addToBasket(unsigned short productID, unsigned short quantity) {
    return; // Zostanie zaimplementowane w projekcie - niepotrzebne w zad 3.
}

void Customer::removeFromBasket(unsigned short productID, unsigned short quantity) {
    return; // Zostanie zaimplementowane w projekcie - niepotrzebne w zad 3.
}

void Customer::clearBasket() {
    basket.clear();
    return;
}

string Customer::getInfo() {
    if (isBusiness) return "Business client\n" + getName() + "\nTax no: " + getTaxNumber() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
    else return getName() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
}
