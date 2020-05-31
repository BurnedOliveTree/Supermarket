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

class ShopInterface {
public:
    virtual void run() = 0;
    virtual std::string event() = 0;
    virtual void executeQueues() = 0;
    virtual bool generate() = 0;
    virtual void checkCustomers() = 0;
    virtual int createCashDesk() = 0;
    virtual int createCustomer() = 0;
    virtual int createEmployee() = 0;
    virtual int createProduct() = 0;
};


class Shop : public ShopInterface {
/// Shop object, representing the whole shop, containing all other objects (Employees, Customers, CashDesks etc.)
    Container<CashDesk> cashDesks;
    Container<Customer> customers;
    Container<Employee> employees;
    Container<Product> products;
    unsigned short maxTime;
    unsigned short eventsPerTick;
    unsigned short scanSpeed;

    void constructor(unsigned long argTime, unsigned short argEvents);
    std::string formatHour(unsigned long minutes);
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
    int createCashDesk();
    int createCustomer();
    int createEmployee();
    int createProduct();
};

#endif /* Shop_hpp */
