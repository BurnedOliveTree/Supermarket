//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Invoice.hpp"
#include "Customer.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <ctime>
#include <fstream>
#include <time.h>
#include <exception>

using namespace std;

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
