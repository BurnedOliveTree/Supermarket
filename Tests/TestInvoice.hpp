//
//  TestInvoice.hpp
//  Zadanie 3
//
//  Created by Paweł Müller on 08/04/2020.
//

#ifndef TestInvoice_hpp
#define TestInvoice_hpp

#include "Product.hpp"
#include "Bill.hpp"
#include "Customer.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class TestInvoice {
    vector<Product> products;
    vector<Customer> buyers;
    vector<Customer> sellers;
    vector<Invoice> invoices;
    vector<Product> *productsPointer;
    
public:
    TestInvoice();
    void menu();
    
private:
    void editElementMenu(string text, char elementChoice);
    
    int consumerChoice(vector<Customer> list);
    int invoiceChoice(vector<Invoice> list);

    void editConsumer(Customer &consumer);
    void editInvoice(Invoice &invoice);
    
    void editProducts(Invoice &invoice);
    
    void showInvoice(Invoice invoice);
};

#endif /* TestInvoice_hpp */
