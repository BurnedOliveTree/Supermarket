#include "Shop.hpp"

amount Shop::getCustomerAmount() {
/// returns the amount of Customer that are in the shop
    return customerContainer.size();
}

void Shop::createCustomer(amount argID) {
/// calls the Customer constructor, appending him to the vector of all customers in this shop
    customerContainer.push_back(Customer(argID));
}

Customer& Shop::findCustomer(amount argID) {
/// returns the adress of Customer object based on a given ID
    for (int i=getCustomerAmount()-1; i>=0; --i)
        if (customerContainer[i].getID() == argID)
            return customerContainer[i];
    throw "ValueError: tried to return an object through ID that doesn't correspond to any of the existing ones.";
}
