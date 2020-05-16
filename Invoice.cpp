//
//  Invoice.cpp
//  Zadanie 3
//
//  Created by Paweł Müller on 07/04/2020.
//

#include "Invoice.hpp"
#include "Consumer.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <ctime>
#include <fstream>
#include <time.h>
#include <exception>

using namespace std;

Invoice::Invoice(bool argIsPayed, time_t argDate, int argNumber, Consumer argBuyer, Consumer argSeller, map<unsigned short, unsigned short> argProducts) {
    editInvoice(argIsPayed, argDate, argNumber, argBuyer, argSeller, argProducts);
}

void Invoice::editInvoice(bool argIsPayed, time_t argDate, int argNumber, Consumer argBuyer, Consumer argSeller, map<unsigned short, unsigned short> argProducts) {
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
bool Invoice::getIsPayed() {
    return isPayed;
}

time_t Invoice::getDate() {
    return date;
}

int Invoice::getNumber() {
    return number;
}

Consumer Invoice::getBuyer() {
    return buyer;
}

Consumer Invoice::getSeller() {
    return seller;
}

map<unsigned short, unsigned short> Invoice::getProducts() {
    return products;
}


// Setters:
void Invoice::setIsPayed(bool newStatus) {
    isPayed = newStatus;
    return;
}

void Invoice::setDate(time_t newDate) {
    date = newDate;
    return;
}

void Invoice::setBuyer(Consumer newBuyer) {
    buyer = newBuyer;
    return;
}

void Invoice::setSeller(Consumer newSeller) {
    seller = newSeller;
    return;
}

void Invoice::setNumber(int newNumber) {
    number = newNumber;
    return;
}

void Invoice::setStock(vector<Product> *argStock) {
    stock = argStock;
}

void Invoice::setProducts(map<unsigned short, unsigned short> newProducts) {
    products = newProducts;
    return;
}


// Tools to edit products:
void Invoice::addProduct(unsigned short newProductID, unsigned short newQuantity) {
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

void Invoice::removeProduct(unsigned short removeProductID, unsigned short removeQuantity) {
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

// Additional features:
string Invoice::generate() {
    vector<Product> stockList = *stock;
    char tempTime [80];
    strftime (tempTime, 80 , "%F", localtime(&date));
    string output = "", temp = "", spaces = "                                   ";
    
    for (int i = 0; i < 78; i++) output += "_";
    output += "\n";
    for (int i = 0; i < 30; i++) output += " ";
    output += "INVOICE  no. " + to_string(number) + "\n";
    output += "FROM: \n" + seller.getInfo() + "\n\n";
    output += "BILL TO: \n" + buyer.getInfo() + "\n\n";
    for (int i = 0; i < 78; i++) output += "_";
    output +="\n| Name                   | Qty | Netto | Brutto | VAT | VAT amt | Brutto amt |\n";
    if (products.empty()) output += "No products given.";
    else {
        for (auto productPair:products) {
            output += "| ";
            for (Product product: stockList) {
                if (product.getID() == productPair.first) {
                    temp = product.getName() + spaces;
                    for (int i = 0; i < 22; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.getQuantity()) + spaces;
                    for (int i = 0; i < 3; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.getPrice()) + spaces;
                    for (int i = 0; i < 5; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.calculatePriceBrutto()) + spaces;
                    for (int i = 0; i < 6; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.getVAT()) + spaces;
                    for (int i = 0; i < 3; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.getVAT() * product.getQuantity() * product.getPrice()) + spaces;
                    for (int i = 0; i < 7; i++) output += temp[i];
                    output +=  " | ";
                    
                    temp = to_string(product.calculatePriceBrutto() * product.getQuantity()) + spaces;
                    for (int i = 0; i < 10; i++) output += temp[i];
                    output +=  " |\n";
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 78; i++) output += "_";
    output += "\n";
    return output;
}

void Invoice::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
    return;
}
