//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Shop_hpp
#define Shop_hpp

#include "Product.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "CashDesk.hpp"

#include <iostream> // będzie <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>

template <typename T, unsigned short maxArg=65535>
struct Container {
/// Container structure containing std::vector of specific objects, maximum amounts of them and their current "iterator" - a special value that is the new objects ID
    unsigned short maxAmount = maxArg;
    unsigned short iterator = 0;
    std::vector<T> container;
    
    unsigned long size() {
        return container.size();
    }
    T& operator[](unsigned long index) {
        return container[index];
    }
};

class Shop {
/// Shop object, representing the whole shop, containing all other objects (Employees, Customers, CashDesks etc.)
    Container<CashDesk> cashDesks;
    Container<Customer> customers;
    Container<Employee> employees;
    Container<Product> products;
    unsigned short time;

public:
    Shop();
    Shop(unsigned long argTime);
    Shop(string filename);
    Shop(char *arguments[]);
    void run();
    void event();
    void executeQueues();
    unsigned short getCashDeskAmount();
    unsigned short getCustomerAmount();
    unsigned short getEmployeeAmount();
    unsigned short getProductAmount();
    int createCashDesk();
    int createCustomer();
    int createEmployee();
    int createProduct();
    Customer& findCustomer(unsigned short argID);
    Product& findProduct(unsigned short argID);
};

#endif /* Shop_hpp */
