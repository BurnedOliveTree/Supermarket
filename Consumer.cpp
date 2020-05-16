//
//  Consumer.cpp
//  Zadanie 3
//
//  Created by Paweł Müller on 07/04/2020.
//

#include "Consumer.hpp"

#include <iostream>

using namespace std;

Consumer::Consumer(bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
    basket.clear();
    editConsumer(argIsBusiness, argName, argTaxNumber, argStreet, argBuildingNumber, argPostcode, argCity, argCountry);
}
void Consumer::editConsumer(bool argIsBusiness, string argName, string argTaxNumber, string argStreet, string argBuildingNumber, string argPostcode, string argCity, string argCountry) {
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
bool Consumer::getIsBusiness() {
    return isBusiness;
}
string Consumer::getName() {
    return name;
}
string Consumer::getTaxNumber() {
    return taxNumber;
}
string Consumer::getStreet() {
    return street;
}
string Consumer::getBuildingNumber() {
    return buildingNumber;
}
string Consumer::getPostcode() {
    return postcode;
}
string Consumer::getCity() {
    return city;
}
string Consumer::getCountry() {
    return country;
}
map<unsigned short, unsigned short> Consumer::getBasket() {
    return basket;
}

//Setters:
void Consumer::setIsBusiness(bool newIsBusiness) {
    isBusiness = newIsBusiness;
    return;
}

void Consumer::setName(string newName) {
    name = newName;
    return;
}

void Consumer::setTaxNumber(string newTaxNumber) {
    taxNumber = newTaxNumber;
    return;
}

void Consumer::setStreet(string newStreet) {
    street = newStreet;
    return;
}

void Consumer::setBuildingNumber(string newBuildingNumber) {
    buildingNumber = newBuildingNumber;
    return;
}

void Consumer::setPostcode(string newPostcode) {
    postcode = newPostcode;
    return;
}

void Consumer::setCity(string newCity) {
    city = newCity;
    return;
}

void Consumer::setCountry(string newCountry) {
    country = newCountry;
    return;
}


// Tools to edit Basket:
void Consumer::setBasket(map<unsigned short, unsigned short> newBasket) {
    basket = newBasket;
    return;
}

void Consumer::addToBasket(unsigned short productID, unsigned short quantity) {
    return; // Zostanie zaimplementowane w projekcie - niepotrzebne w zad 3.
}

void Consumer::removeFromBasket(unsigned short productID, unsigned short quantity) {
    return; // Zostanie zaimplementowane w projekcie - niepotrzebne w zad 3.
}

void Consumer::clearBasket() {
    basket.clear();
    return;
}

string Consumer::getInfo() {
    if (isBusiness) return "Business client\n" + getName() + "\nTax no: " + getTaxNumber() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
    else return getName() + "\n" + getStreet() + " " + getBuildingNumber() + "\n" + getPostcode() + " " + getCity() + "\n" + getCountry();
}
