#include "Customer.hpp"

Customer::Customer(amount argID) {
/// Customer object constructor, a primitive version of
    objID = argID;
}

amount Customer::getID() {
/// returns the ID of Customer object
    return objID;
}
