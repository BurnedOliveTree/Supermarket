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
    customers.maxAmount = values[2];
    customers.maxAmount = values[3];
}

Shop::Shop(char *arguments[]) {
    //odczyt argumentow przekazanych bezposrednio
}

void Shop::run() {
/// main method of class, which simulates the whole shop
    createProduct();
    createCashDesk();
    createEmployee();
    if (customers.maxAmount == 65535)
        customers.maxAmount = time * 0.8; // a temporary mean
    std::srand(std::time(nullptr));
    for (unsigned short i = 0; i < time; ++i) {
        event();
        executeQueues();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Shop::event() {
    double variable = sin(customers.size() / 2 * M_PI / customers.maxAmount);
    int custID, otherID;
    unsigned short diceRoll = std::rand()%100;
    if (diceRoll <= 100 * (1 - variable)) {
    // a new customer enters the shop
        custID = createCustomer();
        if (custID > -1)
            std::cout << "Customer " << custID << " have entered the shop" << std::endl; // to be changed into return
        else
            std::cout << "A maximum value of customers has been reached, nothing happens" << std::endl;
    }
    else if (diceRoll <= 100 - 40 * variable) {
    // customer adds something to their basket
        custID = std::rand() % customers.size();
        otherID = std::rand() % products.size();
        customers[custID].addToBasket(otherID, 1); // 1 should be change into mathematical equation returning mostly 1; and shouldn't otherID be findProduct(otherID) instead?
        // wywal ten produkt z active jeśli już jest w pełni wzięty
        std::cout << "Customer " << customers[custID].getID() << " has added a/an " << products[otherID].getName() << " into his basket" << std::endl;
    }
    else if (diceRoll <= 100 - 10 * variable) {
    // customer joins the queue to a CashDesk
        // klient już może być w kasie, więc też może być busy, więc ten sam problem z while, więc też dla nich trzeba używać active. AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        custID = std::rand() % customers.size();
        // while(!cashDesks[otherID].getState()) - potential of an infinite loop, have to make sure first that there is one CashDesk open or check just for open CashDesks; also, it needs to be a do{...}while;
        otherID = std::rand() % cashDesks.size();
        cashDesks[otherID].push(customers.find(custID));
        std::cout << "Customer " << customers[custID].getID() << " has entered the queue to cash desk " << cashDesks[otherID].getID() << std::endl;
    }
    else if (diceRoll <= 100 - 5 * variable) {
    // random cashDesk changes it status (open / close)
        otherID = std::rand() % cashDesks.size();
        if (cashDesks[otherID].getState()) {
            Employee* freed = cashDesks[otherID].close();
            std::cout << "Cash desk " << cashDesks[otherID].getID() << " has just closed, freeing employee " << freed -> getID() << std::endl;
            employees.active.push_back(freed);
            cashDesks.active.erase(cashDesks.active.begin() + cashDesks.findActive(cashDesks[otherID].getID()));
        }
        else {
            custID = std::rand() % employees.activeSize();
            cashDesks[otherID].open(&employees[custID]);
            employees.active.erase(employees.active.begin() + employees.findActive(employees[custID].getID()));
            cashDesks.active.push_back(&cashDesks[otherID]);
            std::cout << "Cash desk " << cashDesks[otherID].getID() << " has just opened and employee " << employees[custID].getID() << " has been assigned to it" << std::endl;
        }
    }
    // else if - a random Employee changes shifts of another on a random CashDesk
    else {
    // customer asks employee about something
        std::cout << "A random customer has asked a random employee about most random of things" << std::endl;
    }
    std::cout << std::endl;
}

void Shop::executeQueues() {
    Customer* custPoint = nullptr;
    for (unsigned long i = 0; i < cashDesks.size(); ++i) { // size should be maxAmount
        if (cashDesks[i].getState()) {
            custPoint = cashDesks[i].scan(scanSpeed);
            if (custPoint != nullptr) {
                // zaplac, wyjdz, stworz rachunek i wgl
            }
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
        // push back active
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
        products.container.push_back(Product("Banana", products.iterator, 320, 23, 8, 0));
        // push back active
        products.iterator++;
        return products.iterator - 1;
    }
    return -1;
}
