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
#include "Bill.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
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
    std::vector<T*> container;
    std::vector<T*> active;
    
    unsigned long size() {
        return container.size();
    }
    unsigned long activeSize() {
        return active.size();
    }
    T* operator[](unsigned long index) {
        return container[index];
    }
    unsigned long findActive(unsigned short argID) {
        for (unsigned long i = 0; i < activeSize(); ++i) {
            if (active[i] -> getID() == argID)
                return i;
        }
        return -1;
    }
    unsigned long findAll(unsigned short argID) {
        for (unsigned long i = 0; i < size(); ++i) {
            if (container[i] -> getID() == argID)
                return i;
        }
        return -1;
    }
    T* find(unsigned short argID) {
    /// returns the adress of T object based on a given ID
        for (unsigned long i=container.size()-1; i>=0; --i)
            if (container[i] -> getID() == argID) {
                return container[i];
            }
        return nullptr;
    }
};

struct CustData {
/// structure holding data to create Customer objects from (this exist so that we don't have to keep getting data by opening the file over and over again)
    std::string name;
    std::string street;
    std::string city;
    std::string country;
    CustData(std::string argName, std::string argStreet, std::string argCity, std::string argCountry) {
        name = argName;
        street = argStreet;
        city = argCity;
        country = argCountry;
    }
};

class ShopInterface {
public:
    virtual void run() = 0;
    virtual std::string event() = 0;
    virtual void executeQueues() = 0;
    virtual bool generate() = 0;
    virtual void checkCustomers() = 0;
};


class Shop : public ShopInterface {
/// Shop object, representing the whole shop, containing all other objects (Employees, Customers, CashDesks etc.)
    Container<CashDesk> cashDesks;
    Container<Customer> customers;
    Container<Employee> employees;
    Container<Product> products;
    std::vector<CustData> customersData;
    unsigned short maxTime;
    unsigned short eventsPerTick;
    unsigned short billNumber;

    void constructor(unsigned long argTime, unsigned short argEvents);
    std::string formatHour(unsigned long minutes);
    bool createCashDesks();
    void loadCustomers(std::string filename);
    bool createEmployees(std::string filename);
    bool createProducts(std::string filename);
    int createCashDesk();
    int createCustomer();
    int createEmployee(std::string name, unsigned short scanSpeed);
    int createProduct(std::string name, unsigned int price, unsigned char VAT, unsigned short quantity, Measure unit);
public:
    Shop();
    Shop(unsigned long argTime, unsigned short argEvents);
    Shop(std::string filename);
    Shop(char *arguments[], int argc);
    ~Shop();
    void run();
    std::string event();
    void executeQueues();
    bool generate();
    void checkCustomers();
};

#endif /* Shop_hpp */
