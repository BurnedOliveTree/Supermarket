//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"
#include <fstream>

Shop::Shop() {
/// default constructor with pre-set parameters
    std::cout << "started simulation with default arguments: 20 seconds duration and 3 events per second" << std::endl << std::endl;
    constructor(20, 3);
}

Shop::Shop(unsigned long argTime, unsigned short argEvents) {
/// default constructor without pre-set parameters
    constructor(argTime, argEvents);
}

Shop::Shop(string filename) {
/// reading parameters from files
    unsigned short values[2] = {};
    char i = 0;

    ifstream file;
    file.open(filename);
    if (file >> values[i++]) {}
    else cout << "File error." << endl;
    file.close();

    constructor(values[0], values[1]);
}

Shop::Shop(char *arguments[], int argc) {
/// reading parameters directly from console
    if (argc != 3)
        throw "Uncorrect number of arguments was given through console";
    else {
        constructor(std::stoi(arguments[1]), std::stoi(arguments[2]));
    }
}

void Shop::constructor(unsigned long argTime, unsigned short argEvents) {
/// a basic method for all constructors
    maxTime = argTime;
    cashDesks.maxAmount = ceil(0.2 * (float)argTime);
    customers.maxAmount = ceil(0.8 * (float)argTime);
    // employees amount needs always to be bigger than the amount of CashDesks, otherwise program is going to struggle
    employees.maxAmount = ceil(0.3 * (float)argTime);
    products.maxAmount = 1.2 * argTime;
    eventsPerTick = argEvents;
    scanSpeed = argEvents * 2;
}

Shop::~Shop() {
    for (long j = cashDesks.activeSize()-1; j > -1; --j)
        for (long i = cashDesks[j]->size()-1; i > -1; --i )
            delete cashDesks[j]->pop();
    for (long i = customers.activeSize()-1; i > -1; --i)
        delete customers.active[i];
    for (long i = cashDesks.size()-1; i > -1; --i)
        delete cashDesks[i];
    for (long i = employees.size()-1; i > -1; --i)
        delete employees[i];
    for (long i = products.size()-1; i > -1; --i)
        delete products[i];
}

void Shop::run() {
/// main method of class, which simulates the whole shop
    std::srand((unsigned int)std::time(nullptr));
    std::ofstream log("log.txt");
    std::string temp;
    unsigned long currTime = 480;
    generate();
    for (unsigned short i = 0; i < maxTime; ++i) {
        for (unsigned short j = 0; j < eventsPerTick; ++j) {
            temp = event();
            if (temp != "")
                temp = formatHour(currTime+i) + " " + temp;
            std::cout << temp;
            log << temp;
        }
        executeQueues();
        checkCustomers();
        std::this_thread::sleep_for(std::chrono::seconds(eventsPerTick / 2));
    }
    log.close();
}

std::string Shop::event() {
/// a crucial method in simulation - randomly selects and resolve an event
    std::stringstream buff;
    double variable = sin(customers.size() / 2 * M_PI / customers.maxAmount);
    unsigned short diceRoll = std::rand()%100;

    if (diceRoll <= 100 * (1 - variable)) {
    /// a new customer enters the shop
        int customerID = createCustomer();

        if (customerID > -1)
            buff << "Customer " << customers.find(customerID)->getName() << " (ID " << customerID << ") has entered the shop" << std::endl << std::endl;
        else
            buff << "A maximum value of customers has been reached, nothing happens" << std::endl << std::endl;
    }
    else if (diceRoll <= 100 - 60 * variable) {
    /// customer adds something to their basket
        if (customers.activeSize() > 0 && products.activeSize() > 0) {
            Customer* randCustomer = customers.active[std::rand() % customers.activeSize()];
            Product* randProduct = products.active[std::rand() % products.activeSize()];
            unsigned short quantity = 1; // wzór, a nie jeden

            randCustomer->addToBasket(randProduct, quantity);
            if (!randProduct->getQuantity())
                products.active.erase(products.active.begin() + products.findActive(randProduct->getID()));
            buff << randCustomer->getName() << " (ID " << randCustomer->getID() << ") has put " << quantity << " " << randProduct->getName() << " (ID " << randProduct->getID() << ") into his basket" << std::endl << std::endl;
        }
    }
    else if (diceRoll <= 100 - 20 * variable) {
    /// customer joins the queue to a CashDesk
        if (customers.activeSize() > 0) {
            Customer* randCustomer = customers.active[std::rand() % customers.activeSize()];
            CashDesk* randCashDesk = cashDesks.active[std::rand() % cashDesks.activeSize()];

            randCashDesk->push(randCustomer);
            customers.active.erase(customers.active.begin() + customers.findActive(randCustomer->getID()));
            buff << "Customer " << randCustomer->getName() << " (ID " << randCustomer->getID() << ") has entered the queue to cash desk " << randCashDesk->getID() << std::endl << std::endl;
        }
    }
    else if (diceRoll <= 100 - 10 * variable) {
    /// random cashDesk changes it status (open / close)
        CashDesk* randCashDesk = nullptr;
        // checks if wee are not closing the last CashDesk
        if (cashDesks.activeSize() > 1)
            randCashDesk = cashDesks[std::rand() % cashDesks.size()];
        else {
            // checks if we have more than one CashDesk (opened or closed)
            if (cashDesks.size() > 1) {
                for (unsigned short i = 0; i < cashDesks.size(); ++i)
                    if (!cashDesks[i]->getState()) {
                        randCashDesk = cashDesks[i];
                        break;
                    }
            }
            else {
                // we don't -> the only CashDesk in Shop should always stay open
                return buff.str();
            }
        }
        Employee* randEmployee = nullptr;

        if (randCashDesk->getState()) {
            randEmployee = randCashDesk->close();
            buff << "Cash desk (ID " << randCashDesk -> getID() << ") has just closed, freeing employee " << randEmployee -> getID() << std::endl << std::endl;
            employees.active.push_back(randEmployee);
            cashDesks.active.erase(cashDesks.active.begin() + cashDesks.findActive(randCashDesk->getID()));
        }
        else {
            randEmployee = employees.active[std::rand() % employees.activeSize()];
            randCashDesk->open(randEmployee);
            employees.active.erase(employees.active.begin() + employees.findActive(randEmployee->getID()));
            cashDesks.active.push_back(randCashDesk);
            buff << "Cash desk (ID " << randCashDesk->getID() << ") has just opened and employee " << randEmployee->getID() << " has been assigned to it" << std::endl << std::endl;
        }
    }
    else if (diceRoll <= 100 - 5 * variable) {
    /// a random Employee changes shifts of another on a random CashDesk
        if (employees.activeSize() > 0)
        {
            Employee* randEmployee = employees.active[std::rand() % employees.activeSize()];
            CashDesk* randCashDesk = cashDesks.active[std::rand() % cashDesks.activeSize()];

            employees.active.push_back(randCashDesk->assign(randEmployee));
            employees.active.erase(employees.active.begin() + employees.findActive(randEmployee->getID()));
            buff << randEmployee->getName() << " (ID " << randEmployee->getID() << ") has replaced another employee as a cashier at cash desk (ID " << randCashDesk->getID() << ")" << std::endl << std::endl;
        }
    }
    else {
    /// customer asks employee about the price
        if (customers.activeSize() > 0 && products.activeSize() > 0 && employees.activeSize() > 0){
        Customer* randCustomer = customers.active[std::rand() % customers.activeSize()];
        Employee* randEmployee = employees.active[std::rand() % employees.activeSize()];
        Product* randProduct = products.active[std::rand() % products.activeSize()];
        
        buff << randCustomer->getName() << " (ID " << randCustomer->getID() << ") has asked a " << randEmployee->getName() << " (ID " << randEmployee->getID() << ") about the price of " << randProduct->getName() << " (ID " << randProduct->getID() << ") and it's " << randProduct->getPrice()/100 << "." << randProduct->getPrice()%100  << std::endl << std::endl;
        }
    }
    return buff.str();
}

void Shop::executeQueues() {
/// iterates over all active CashDesks and calls scan() form each, also resolve Customers payment for Product's in its basket, if all items were scanned
    for (unsigned long i = 0; i < cashDesks.activeSize(); ++i) {
        if (cashDesks.active[i]->size()) {
            Customer* custPoint = cashDesks.active[i]->scan(scanSpeed);
            if (custPoint != nullptr) {
                // cashDesks.active[i] += wartość pieniędzy z rachunku
                // custPoint.stwórzRachunekIGoWrzućDoPliku
                customers.container.erase(customers.container.begin() + customers.findAll(custPoint->getID()));
                delete custPoint;
            }
        }
    }
}

bool Shop::generate() {
/// generates all the needed object before running
    for (int i = products.maxAmount - 1; i >= 0; --i)
        if (createProduct() == -1)
            return false;
    for (int i = cashDesks.maxAmount - 1; i >= 0; --i)
        if (createCashDesk() == -1)
            return false;
    for (int i = employees.maxAmount - 1; i >= 0; --i)
        if (createEmployee() == -1)
            return false;
    // assigning random employees to few CashDesks, so at least some will be open at the start of simulation
    float temp = 0.25 * cashDesks.size();
    Employee* randEmployee = nullptr;
    for (int i = ceil(temp) - 1; i > -1; --i) {
        randEmployee = employees.active[std::rand() % employees.activeSize()];
        cashDesks[i]->open(randEmployee);
        employees.active.erase(employees.active.begin() + employees.findActive(randEmployee->getID()));
        cashDesks.active.push_back(cashDesks[i]);
    }
    return true;
}

void Shop::checkCustomers() {
/// resets customers iterator if there aren't any clients in Shop, but the iterator is at its max value
    if (customers.size() == 0)
        customers.iterator = 0;
}

int Shop::createCashDesk() {
/// calls the CashDesk constructor, appending him to the vector of all cash desks in this shop
    if (cashDesks.iterator + 1 <= cashDesks.maxAmount) {
        CashDesk* p = new CashDesk(cashDesks.iterator, 0);
        cashDesks.container.push_back(p);
        cashDesks.iterator++;
        return cashDesks.iterator - 1;
    }
    return -1;
}

int Shop::createCustomer() {
/// calls the Customer constructor, appending him to the vector of all customers in this shop
    if (customers.iterator + 1 <= customers.maxAmount) {
        Customer* p = new Customer(customers.iterator, false, "Jan K", "1234567890", "Sezamkowa", "18", "05-800", "Warszawa", "Polska");
        customers.container.push_back(p);
        customers.active.push_back(p);
        customers.iterator++;
        return customers.iterator - 1;
    }
    return -1;
}

int Shop::createEmployee() {
/// calls the Employee constructor, appending him to the vector of all products in this shop
    if (employees.iterator + 1 <= employees.maxAmount) {
        Employee* p = new Employee(employees.iterator, "Geralt z Rivii");
        employees.container.push_back(p);
        employees.active.push_back(p);
        employees.iterator++;
        return employees.iterator - 1;
    }
    return -1;
}

int Shop::createProduct() {
/// calls the Product constructor, appending him to the vector of all products in this shop
    if (products.iterator + 1 <= products.maxAmount) {
        Product* p = new Product("Banana", products.iterator, 320, 23, 8, pcs); // tan(((double)(std::rand() % 100) / 100 + M_PI / 2) / M_PI)
        products.container.push_back(p);
        products.active.push_back(p);
        products.iterator++;
        return products.iterator - 1;
    }
    return -1;
}

std::string Shop::formatHour(unsigned long minutes) {
    std::string result = std::to_string(minutes / 60) + ":";
    if (minutes % 60 < 10)
        result += "0";
    return result + std::to_string(minutes % 60);
}
