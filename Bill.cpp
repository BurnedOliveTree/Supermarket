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
bool Bill::getIsPayed() const{
    return isPayed;
}

time_t Bill::getDate() const {
    return date;
}

unsigned short Bill::getID() const {
    return ID;
}

Customer Bill::getBuyer() const {
    return buyer;
}

Customer Bill::getSeller() const {
    return seller;
}

map<unsigned short, unsigned short> Bill::getProducts() const {
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

string Invoice::generate() const {
    char invoiceWidth = 78;

    vector<Product> stockList = *stock;

    string output = stringAlign("_", 2, invoiceWidth, "_");

    output += "\n";
    output += "|" + stringAlign("INVOICE", 2, invoiceWidth - 2) + "|\n";
    output += "|" + stringAlign("#" + to_string(ID), 2, invoiceWidth - 2) + "|\n";

    output += "|" + stringAlign("BILL FROM:", 2, (invoiceWidth - 4) / 2) + "  " + stringAlign("BILL TO:", 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getName(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getName(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + " " + seller.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getStreet() + " " + buyer.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + " " + seller.getPostcode(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getCity() + " " + buyer.getPostcode(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getTaxNumber(), 2, (invoiceWidth - 4) / 2) + "|\n";

    output += "|" + stringAlign("_", 2, invoiceWidth - 2, "_") + "|\n";

    output += "| NAME                   | QTY | NETTO | BRUTTO | VAT | VAT AMT | BRUTTO AMT |\n";
    for (auto productPair:products) {
        for (Product product: stockList) {
            if (product.getID() == productPair.first) {
                output += "|";
                output += stringAlign(product.getName(), 0, 24);
                output += "|";
                output += stringAlign(to_string(product.getQuantity()), 0, 5);
                output += "|";
                output += stringAlign(to_string(product.getPrice()), 0, 7);
                output += "|";
                output += stringAlign(to_string(product.calculatePriceBrutto()), 0, 8);
                output += "|";
                output += stringAlign(to_string(product.getVAT()) + "%", 0, 5);
                output += "|";
                output += stringAlign(to_string(product.getVAT() * product.getQuantity() * product.getPrice()), 0, 9);
                output += "|";
                output += stringAlign(to_string(product.calculatePriceBrutto() * product.getQuantity()), 0, 12);
                output += "|\n";
                break;
            }
        }
    }
    output += "|" + stringAlign(".", 2, invoiceWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, invoiceWidth - 14) + "XXXXXXXXXXXX|\n";
    output += "|" + stringAlign("TMS: TTTTT   ID: " + to_string(ID), 2, invoiceWidth - 2) + "|\n";

    output += stringAlign("¯", 0, invoiceWidth, "¯") += "\n";
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

string Receipt::generate() const {
    char receiptWidth = 40;
    
    vector<Product> stockList = *stock;
    string output = stringAlign("_", 0, 40, "_");
    
    output += "\n";
    output += "|" + stringAlign(seller.getName(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + " " + seller.getBuildingNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + " " + seller.getPostcode(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("RECEIPT", 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "| NAME          QTY  x PRICE   VALUE   |\n";

    for (auto productPair:products) {
        for (Product product: stockList) {
            if (product.getID() == productPair.first) {
                output += "|";
                output += stringAlign(product.getName(), 0, 14);
                output += " ";
                output += stringAlign(to_string(product.getQuantity()), 0, 5);
                output += "x ";
                output += stringAlign(to_string(product.calculatePriceBrutto()), 0, 7);
                output += " ";
                output += stringAlign(to_string(product.calculatePriceBrutto() * product.getQuantity()), 0, 8);
                output += "|\n";
                break;
            }
        }
    }
    
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, receiptWidth - 10) + "XXXXXXXX|\n";
    output += "|" + stringAlign("TMS: TTTTT   ID: ", 0, receiptWidth - 2) + "|\n";

    output += stringAlign("¯", 0, receiptWidth, "¯") += "\n";
    return output;
}

void Receipt::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
    return;
}
