//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"
#include <fstream>

Shop::Shop() {
    //konstruktor domyslny
}

Shop::Shop(unsigned long argTime) {
    //konstruktor niedomyslny
    time = argTime;
    cashDesks.maxAmount = 0.2 * argTime;
    customers.maxAmount = 0.8 * argTime;
    employees.maxAmount = 0.3 * argTime;
    products.maxAmount = 1.2 * argTime;
    scanSpeed = 5; // 5, hm
}

Shop::Shop(string filename) {
    //odczyt pliku i przekazanie argumentow
    unsigned short values[5] = {};
    char i = 0;
    
    ifstream file;
    file.open(filename);
    if (file >> values[i++]) {}
    else cout << "File error." << endl;
    
    file.close();
    
    //czas, ilosc kas, ilosc pracownikow, ilosc klientow
    time = values[0];
    scanSpeed = 5; // 5, hm
    cashDesks.maxAmount = values[1];
    customers.maxAmount = values[3];
    employees.maxAmount = values[2];
}

Shop::Shop(char *arguments[]) {
    //odczyt argumentow przekazanych bezposrednio
}

void Shop::run() {
/// main method of class, which simulates the whole shop
    generate();
    std::srand(std::time(nullptr));
    for (unsigned short i = 0; i < time; ++i) {
        event();
        executeQueues();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Shop::event() {
    double variable = sin(customers.size() / 2 * M_PI / customers.maxAmount);
    unsigned short diceRoll = std::rand()%100;

    if (diceRoll <= 100 * (1 - variable)) {
    // a new customer enters the shop
        int customerID = createCustomer();

        if (customerID > -1)
            std::cout << "Customer " << customers.find(customerID)->getName() << " (ID " << customerID << ") have entered the shop" << std::endl;
        else
            std::cout << "A maximum value of customers has been reached, nothing happens" << std::endl;
    }
    else if (diceRoll <= 100 - 60 * variable) {
    // customer adds something to their basket
        Customer* randCustomer = customers.active[std::rand() % customers.activeSize()];
        Product* randProduct = products.active[std::rand() % products.activeSize()];
        unsigned short quantity = 1;

        randCustomer->addToBasket(randProduct, quantity);
        if (!randProduct->getQuantity())
            products.active.erase(products.active.begin() + products.findActive(randProduct->getID()));
        std::cout << randCustomer->getName() << " (ID " << randCustomer->getID() << ") has put " << quantity << " " << randProduct->getName() << "(ID " << randProduct->getID() << ") into his basket" << std::endl;
    }
    else if (diceRoll <= 100 - 20 * variable) {
    // customer joins the queue to a CashDesk
        Customer* randCustomer = customers.active[std::rand() % customers.activeSize()];
        CashDesk* randCashDesk = cashDesks.active[std::rand() % cashDesks.activeSize()];

        randCashDesk->push(randCustomer);
        std::cout << "Customer " << randCustomer->getID() << " has entered the queue to cash desk " << randCashDesk->getID() << std::endl;
    }
    else if (diceRoll <= 100 - 10 * variable) {
    // random cashDesk changes it status (open / close)
        CashDesk* randCashDesk = &cashDesks[std::rand() % cashDesks.size()];
        Employee* randEmployee = nullptr;

        if (randCashDesk->getState()) {
            randEmployee = randCashDesk->close();
            std::cout << "Cash desk (ID " << randCashDesk -> getID() << ") has just closed, freeing employee " << randEmployee -> getID() << std::endl;
            employees.active.push_back(randEmployee);
            cashDesks.active.erase(cashDesks.active.begin() + cashDesks.findActive(randCashDesk->getID()));
        }
        else {
            randEmployee = employees.active[std::rand() % employees.activeSize()];
            randCashDesk->open(randEmployee);
            employees.active.erase(employees.active.begin() + employees.findActive(randEmployee->getID()));
            cashDesks.active.push_back(randCashDesk);
            std::cout << "Cash desk (ID" << randCashDesk->getID() << ") has just opened and employee " << randEmployee->getID() << " has been assigned to it" << std::endl;
        }
    }
    else if (diceRoll <= 100 - 5 * variable) {
    // a random Employee changes shifts of another on a random CashDesk
        Employee* randEmployee = employees.active[std::rand() % employees.activeSize()];
        CashDesk* randCashDesk = cashDesks.active[std::rand() % cashDesks.activeSize()];

        employees.active.push_back(randCashDesk->assign(randEmployee));
        employees.active.erase(employees.active.begin() + employees.findActive(randEmployee->getID()));
        std::cout << randEmployee->getName() << " (ID " << randEmployee->getID() << ") has replaced another employee as a cashier at cash desk (ID " << randCashDesk->getID() << ")" << std::endl;
    }
    else {
    // customer asks employee about something
        std::cout << "A random customer has asked a random employee about most random of things" << std::endl;
    }
    std::cout << std::endl;
}

void Shop::executeQueues() {
    Customer* custPoint = nullptr;
    for (unsigned long i = 0; i < cashDesks.activeSize(); ++i) {
        custPoint = cashDesks[i].scan(scanSpeed);
        if (custPoint != nullptr) {
            // to jest moment, w którym wszystkie towary klienta zostały zeskanowane, więc powinien zapłacić, dostać rachunek i wyjść (czyli de facto zostać zniszczony)
            // custPoint będzie trzymał wskaźnik na tego klienta (który został już wypchnięty z vector'a kolejki)
        }
    }
}

unsigned short Shop::getCashDeskAmount() {
/// returns the amount of Customer that are in the shop
    return cashDesks.size();
}

unsigned short Shop::getCustomerAmount() {
/// returns the amount of Customer that are in the shop
    return customers.size();
}

unsigned short Shop::getEmployeeAmount() {
/// returns the amount of Customer that are in the shop
    return employees.size();
}

unsigned short Shop::getProductAmount() {
/// returns the amount of Customer that are in the shop
    return products.size();
}

bool Shop::generate() {
/// generates all the needed object before running
    for (unsigned short i = products.maxAmount - 1; i >= 0; --i)
        if (createProduct() == -1)
            return false;
    for (unsigned short i = cashDesks.maxAmount - 1; i >= 0; --i)
        if (createCashDesk() == -1)
            return false;
    for (unsigned short i = employees.maxAmount - 1; i >= 0; --i)
        if (createEmployee() == -1)
            return false;
    return true;
}

int Shop::createCashDesk() {
/// calls the CashDesk constructor, appending him to the vector of all cash desks in this shop
    if (cashDesks.iterator + 1 < cashDesks.maxAmount) {
        cashDesks.container.push_back(CashDesk(cashDesks.iterator, 0));
        cashDesks.iterator++;
        return cashDesks.iterator - 1;
    }
    return -1;
}

int Shop::createCustomer() {
/// calls the Customer constructor, appending him to the vector of all customers in this shop
    if (customers.iterator + 1 < customers.maxAmount) {
        customers.container.push_back(Customer(customers.iterator, false, "Jan K", "1234567890", "Sezamkowa", "18", "05-800", "Warszawa", "Polska"));
        customers.active.push_back(customers.find(customers.iterator));
        customers.iterator++;
        return customers.iterator - 1;
    }
    return -1;
}

int Shop::createEmployee() {
/// calls the Product constructor, appending him to the vector of all products in this shop
    if (employees.iterator + 1 < employees.maxAmount) {
        employees.container.push_back(Employee(employees.iterator, "Geralt", "z Rivii"));
        employees.active.push_back(employees.find(employees.iterator));
        employees.iterator++;
        return employees.iterator - 1;
    }
    return -1;
}

int Shop::createProduct() {
/// calls the Product constructor, appending him to the vector of all products in this shop
    if (products.iterator + 1 < products.maxAmount) {
        products.container.push_back(Product("Banana", products.iterator, 320, 23, 8, pcs));
        products.active.push_back(products.find(products.iterator));
        products.iterator++;
        return products.iterator - 1;
    }
    return -1;
}
