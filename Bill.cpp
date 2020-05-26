//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Bill.hpp"
#include "Customer.hpp"
#include "AddOns/StringOperations.hpp"


#include <iostream>
#include <map>
#include <utility>
#include <ctime>
#include <fstream>
#include <time.h>
#include <exception>

using namespace std;

Bill::Bill(bool argIsPayed, time_t argDate, unsigned short argID, Customer argBuyer, Customer argSeller, map<unsigned short, unsigned short> argProducts) {
    isPayed = argIsPayed;
    date = argDate;
    ID = argID;
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

unsigned short Bill::getID() {
    return ID;
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

void Bill::setID(unsigned short newID) {
    ID = newID;
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



/*   =======================   INVOICE   =======================   */

string Invoice::generate() {
    vector<Product> stockList = *stock;

    string output = "", temp = "", spaces = "                                   ";
    
    for (int i = 0; i < 78; i++) output += "_";
    output += "\n";
    for (int i = 0; i < 30; i++) output += " ";
    output += "INVOICE  no. " + to_string(ID) + "\n";
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





/*   =======================   RECEIPT   =======================   */

string Receipt::generate() {
    char receiptWidth = 40;
    
    vector<Product> stockList = *stock;
    unsigned int value = 0;
    string output = stringAlign("_", 0, 40, "_");
    
    output += "\n";
    output += "|" + stringAlign(seller.getName(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + seller.getBuildingNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + seller.getPostcode(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("RECEIPT", 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "| NAME          QTY  x PRICE   VALUE   |\n";

    for (auto productPair:products) {
        for (Product product: stockList) {
            if (product.getID() == productPair.first) {
                value = product.calculatePriceBrutto() * product.getQuantity();
                output += "|";
                output += stringAlign(product.getName(), 0, 14);
                output += " ";
                output += stringAlign(to_string(product.getQuantity()), 0, 5);
                output += "x ";
                output += stringAlign(to_string(product.calculatePriceBrutto()), 0, 7);
                output += " ";
                output += stringAlign(to_string(value), 0, 8);
                output += "|\n";
                break;
            }
        }
    }
    output += stringAlign("_", 0, 40, "_") += "\n";
    return output;
}

void Receipt::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
    return;
}
