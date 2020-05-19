//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"

amount Shop::getCashDeskAmount() {
/// returns the amount of Customer that are in the shop
    return customerContainer.size();
}

amount Shop::getCustomerAmount() {
/// returns the amount of Customer that are in the shop
    return customerContainer.size();
}

void Shop::createCustomer() {
/// calls the Customer constructor, appending him to the vector of all customers in this shop
    for (unsigned long i=1; i<maxCustomerAmount; ++i)
        if (customerContainer[i].getID())
            customerContainer.push_back(Customer(i));
}

Customer& Shop::findCustomer(amount argID) {
/// returns the adress of Customer object based on a given ID
    for (unsigned long i=getCustomerAmount()-1; i>=0; --i)
        if (customerContainer[i].getID() == argID)
            return customerContainer[i];
    throw "ValueError: tried to return an object through ID that doesn't correspond to any of the existing ones.";
}
