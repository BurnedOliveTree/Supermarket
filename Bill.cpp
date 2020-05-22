//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Bill.hpp"
#include "Customer.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <ctime>
#include <fstream>
#include <time.h>
#include <exception>

using namespace std;

Bill::Bill(bool argIsPayed, time_t argDate, int argNumber, Customer argBuyer, Customer argSeller, map<unsigned short, unsigned short> argProducts) {
    editBill(argIsPayed, argDate, argNumber, argBuyer, argSeller, argProducts);
}

void Bill::editBill(bool argIsPayed, time_t argDate, int argNumber, Customer argBuyer, Customer argSeller, map<unsigned short, unsigned short> argProducts) {
    isPayed = argIsPayed;
    date = argDate;
    number = argNumber;
    buyer = argBuyer;
    seller = argSeller;
    if (argProducts.empty()) {
        products = buyer.getBasket();
    } else {
        products = argProducts;
    }
}

// Getters:
bool Bill::getIsPayed() {
    return isPayed;
}

time_t Bill::getDate() {
    return date;
}

int Bill::getNumber() {
    return number;
}

Customer Bill::getBuyer() {
    return buyer;
}

Customer Bill::getSeller() {
    return seller;
}

map<unsigned short, unsigned short> Bill::getProducts() {
    return products;
}


// Setters:
void Bill::setIsPayed(bool newStatus) {
    isPayed = newStatus;
    return;
}

void Bill::setDate(time_t newDate) {
    date = newDate;
    return;
}

void Bill::setBuyer(Customer newBuyer) {
    buyer = newBuyer;
    return;
}

void Bill::setSeller(Customer newSeller) {
    seller = newSeller;
    return;
}

void Bill::setNumber(int newNumber) {
    number = newNumber;
    return;
}

void Bill::setStock(vector<Product> *argStock) {
    stock = argStock;
}

void Bill::setProducts(map<unsigned short, unsigned short> newProducts) {
    products = newProducts;
    return;
}


// Tools to edit products:
void Bill::addProduct(unsigned short newProductID, unsigned short newQuantity) {
    vector<Product> stockList = *stock;
    bool idExist = false;
    for (Product product: stockList) {
        if (product.getID() == newProductID) idExist = true;
    }
    if (idExist) {
        products.insert({newProductID, newQuantity});
    } else {
        throw invalid_argument("Product does not exist in stock.");
    }
    return;
}

void Bill::removeProduct(unsigned short removeProductID, unsigned short removeQuantity) {
    vector<Product> stockList = *stock;
    unsigned short productQuantity = 0;
    bool idExist = false;
    for (Product product: stockList) {
        if (product.getID() == removeProductID) {
            idExist = true;
            productQuantity = products[removeProductID];
        }
    }
    if (idExist) {
        if (removeQuantity < productQuantity) {
            products[removeProductID] = productQuantity - removeProductID;
        }
        else throw invalid_argument("There are less products then you want to remove.");
    } else throw invalid_argument("Product does not exist in database.");
    return;;
}
