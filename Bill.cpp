//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Bill.hpp"
#include "Customer.hpp"
#include "AddOns/StringOperations.hpp"

#include <utility>
#include <fstream>
#include <exception>

using namespace std;

Bill::Bill(unsigned short argID, Customer argBuyer, Customer argSeller) {
    ID = argID;
    buyer = argBuyer;
    seller = argSeller;
}


// Getters:
unsigned short Bill::getID() const {
    return ID;
}

Customer Bill::getBuyer() const {
    return buyer;
}

Customer Bill::getSeller() const {
    return seller;
}


// Setters:
void Bill::setBuyer(Customer newBuyer) {
    buyer = newBuyer;
}

void Bill::setSeller(Customer newSeller) {
    seller = newSeller;
}

void Bill::setID(unsigned short newID) {
    ID = newID;
}

string Bill::convertPricePLN(unsigned short price) const {
    string prefix = to_string(price / 100), suffix = to_string(price % 100);
    return prefix + "." + (suffix.length() == 1 ? ("0" + suffix) : suffix);
}

string Bill::convertToKg(unsigned short quantity) const {
    string prefix = to_string(quantity / 1000), suffix = to_string(quantity % 1000);
    return prefix + "." + (suffix.length() == 1 ? ("00" + suffix) : (suffix.length() == 2 ? ("0" + suffix) : suffix));
}

void Bill::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
}


/*   =======================   INVOICE   =======================   */

string Invoice::generate() const {
    char invoiceWidth = 90;
    unsigned short priceBrutto = 0, totalBrutto = 0;
    string output = stringAlign("_", 2, invoiceWidth, "_");

    output += "\n";
    output += "|" + stringAlign("INVOICE", 2, invoiceWidth - 2) + "|\n";
    output += "|" + stringAlign("#" + to_string(ID), 2, invoiceWidth - 2) + "|\n";

    output += "|" + stringAlign("BILL FROM:", 2, (invoiceWidth - 4) / 2) + "  " + stringAlign("BILL TO:", 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getName(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getName(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + " " + seller.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getStreet() + " " + buyer.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + " " + seller.getPostcode(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getCity() + " " + buyer.getPostcode(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getTaxNumber()!="0"?buyer.getTaxNumber():" ", 2, (invoiceWidth - 4) / 2) + "|\n";

    output += "|" + stringAlign("_", 2, invoiceWidth - 2, "_") + "|\n";

    output += "| NAME                   |  QTY  | U |  NETTO  |  BRUTTO  | VAT | VAT AMT |  BRUTTO AMT  |\n";
    for (auto basketPair: buyer.getBasket()) {
        Product *product = basketPair.first;
        unsigned short quantity = basketPair.second;
        output += "|";
        output += stringAlign(product -> getName(), 0, 24);
        output += "|";
        output += stringAlign(product -> getMeasureUnits() == g ? convertToKg(quantity) : to_string(quantity), 1, 7);
        output += "|";
        output += stringAlign(product -> getMeasureUnits() == g ? "kg" : "pcs", 2, 3);
        output += "|";
        output += stringAlign(convertPricePLN(product -> getPrice()), 1, 9);
        output += "|";
        output += stringAlign(convertPricePLN(product -> calculatePriceBrutto()), 1, 10);
        output += "|";
        output += stringAlign(to_string(product -> getVAT()) + " %", 1, 5);
        output += "|";
        output += stringAlign(convertPricePLN(product -> getVAT() * quantity * product -> getPrice() / 100 / (product -> getMeasureUnits() == pcs ? 1 : 1000)), 1, 9);
        output += "|";
        priceBrutto = ceil(product -> calculatePriceBrutto() * quantity / (product -> getMeasureUnits() == pcs ? 1 : 1000));
        output += stringAlign(convertPricePLN(priceBrutto), 1, 14);
        output += "|\n";
        totalBrutto += priceBrutto;
    }
    

    output += "|" + stringAlign(".", 2, invoiceWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, invoiceWidth - 14) + stringAlign(convertPricePLN(totalBrutto), 2, 12) + "|\n";
    output += "|" + stringAlign("ID: " + to_string(ID), 0, invoiceWidth - 2) + "|\n";

    output += stringAlign("¯", 0, invoiceWidth, "¯") += "\n";
    return output;
}





/*   =======================   RECEIPT   =======================   */

string Receipt::generate() const {
    char receiptWidth = 40;
    unsigned short priceBrutto = 0, totalBrutto = 0;
    
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

    for (auto basketPair: buyer.getBasket()) {
        Product *product = basketPair.first;
        unsigned short quantity = basketPair.second;
        output += "|";
        output += stringAlign(product -> getName(), 0, 14);
        output += " ";
        output += stringAlign(product -> getMeasureUnits() == g ? convertToKg(quantity) : to_string(quantity), 1, 5);
        output += "x ";
        output += stringAlign(convertPricePLN(product -> calculatePriceBrutto()), 1, 7);
        output += " ";
        priceBrutto = ceil(product -> calculatePriceBrutto() * quantity / (product -> getMeasureUnits() == pcs ? 1 : 1000));
        output += stringAlign(convertPricePLN(priceBrutto), 1, 8);
        output += "|\n";
        totalBrutto += priceBrutto;
    }
    
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, receiptWidth - 10) + stringAlign(convertPricePLN(totalBrutto), 2, 8) + "|\n";
    output += "|" + stringAlign("ID: ", 0, receiptWidth - 2) + "|\n";

    output += stringAlign("¯", 0, receiptWidth, "¯") += "\n";
    return output;
}
