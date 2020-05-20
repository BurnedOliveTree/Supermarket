//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"

void Shop::run(unsigned short time) {
/// main method of class, which simulates the whole shop
    createProduct();
    createCashDesk();
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
        std::cout << "Customer " << customers[custID].getID() << " has added a/an " << products[otherID].getName() << " into his basket" << std::endl;
    }
    else if (diceRoll <= 100 - 10 * variable) {
    // customer joins the queue to a CashDesk
        custID = std::rand() % customers.size();
        // while(!cashDesks[otherID].getState()) - potential of an infinite loop, have to make sure first that there is one CashDesk open or check just for open CashDesks; also, it needs to be a do{...}while;
        otherID = std::rand() % cashDesks.size();
        std::cout << "Customer " << customers[custID].getID() << " has entered the queue to cash desk " << cashDesks[otherID].getID() << std::endl;
    }
    else if (diceRoll <= 100 - 5 * variable) {
    // random cashDesk changes it status (open / close)
        otherID = std::rand() % cashDesks.size();
        if (cashDesks[otherID].getState()) {
            cashDesks[otherID].close();
            // free the employee if he is not freed by close()
            std::cout << "Cash desk " << cashDesks[otherID].getID() << " has just closed" << std::endl;
        }
        else {
            cashDesks[otherID].open();
            // get the employee busy if he is not getting busy by open()
            std::cout << "Cash desk " << cashDesks[otherID].getID() << " has just opened" << std::endl;
        }
    }
    else {
    // customer asks employee about something
        std::cout << "A random customer has asked a random employee about most random of things" << std::endl;
    }
}

void Shop::executeQueues() {
    return;
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
        cashDesks.container.push_back(CashDesk(cashDesks.iterator, 0, 0, 0));
        cashDesks.iterator++;
        return cashDesks.iterator - 1;
    }
    return -1;
}

int Shop::createCustomer() {
/// calls the Customer constructor, appending him to the vector of all customers in this shop
    if (customers.iterator + 1 < customers.maxAmount) {
        customers.container.push_back(Customer(customers.iterator, false, "Jan K", "1234567890", "Sezamkowa", "18", "05-800", "Warszawa", "Polska"));
        customers.iterator++;
        return customers.iterator - 1;
    }
    return -1;
}

int Shop::createProduct() {
/// calls the Product constructor, appending him to the vector of all products in this shop
    if (products.iterator + 1 < products.maxAmount) {
        products.container.push_back(Product("Banana", products.iterator, 320, 23, 8, 0));
        products.iterator++;
        return products.iterator - 1;
    }
    return -1;
}

Customer& Shop::findCustomer(unsigned short argID) {
/// returns the adress of Customer object based on a given ID
    for (unsigned long i=customers.size()-1; i>=0; --i)
        if (customers[i].getID() == argID)
            return customers[i];
    throw "ValueError: tried to return an object through ID that doesn't correspond to any of the existing ones.";
}

Product& Shop::findProduct(unsigned short argID) {
/// returns the adress of Product object based on a given ID
    for (unsigned long i=products.size()-1; i>=0; --i)
        if (products[i].getID() == argID)
            return products[i];
    throw "ValueError: tried to return an object through ID that doesn't correspond to any of the existing ones.";
}
