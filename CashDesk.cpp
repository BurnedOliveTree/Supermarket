//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "CashDesk.hpp"

CashDesk::CashDesk(unsigned short argID, unsigned int cashIn) {
/// CashDesk object constructor
    ID = argID;
    isOpen = false;
    cashAmount = cashIn;
    assignee = nullptr;
    itemsScaned = 0;
}

unsigned short CashDesk::getID() {
/// returns the ID of CashDesk object
    return ID;
}

bool CashDesk::operator ==(unsigned short secondID) {
/// comparison operator overload comparing IDs of CashDesk object and a unsigned short
    if (getID() == secondID)
        return true;
    else
        return false;
}

bool CashDesk::operator !=(unsigned short secondID) {
/// comparison operator overload comparing ID of CashDesk object and a unsigned short
    return !(getID() == secondID);
}

bool CashDesk::operator ==(CashDesk cash2) {
/// comparison operator overload comparing IDs of CashDesk objects
    if (getID() == cash2.getID())
        return true;
    else
        return false;
}

bool CashDesk::operator !=(CashDesk cash2) {
/// comparison operator overload comparing IDs of CashDesk objects
    return !(getID() != cash2.getID());
}

void CashDesk::open(Employee* assigned) {
/// sets this CashDesk status to open
    isOpen = true;
    assigned -> setBusy();
    assignee = assigned;
}

bool CashDesk::getState() {
/// return status of this CashDesk
    return isOpen;
}

Employee* CashDesk::close() {
/// sets this CashDesk status to closed
    isOpen = false;
    assignee -> setFree();
    return assignee;
}

unsigned int CashDesk::getCash() {
    return cashAmount;
}

void CashDesk::addCash(unsigned int n) {
    cashAmount += n;
}

void CashDesk::operator +=(unsigned int n) {
    addCash(n);
}

void CashDesk::setCash(unsigned int n) {
    cashAmount = n;
}

void CashDesk::operator =(unsigned int n) {
    setCash(n);
}

void CashDesk::takeCash(unsigned int n) {
    cashAmount -= n;
}

void CashDesk::operator -=(unsigned int n) {
    takeCash(n);
}

Employee* CashDesk::assign(Employee* assigned) {
/// assigns an Employee to the cash register and returns the previously assigned Employee, if there was any
    Employee* temp = assignee;
    assignee = assigned;
    assigned -> setBusy();
    temp -> setFree();
    return temp;
}

void CashDesk::operator =(Employee* assigned) {
    assign(assigned);
}

void CashDesk::push(Customer* shopper) {
/// assigns a Customer to the CashDesk queue (checking whether Customer is already in a queue will be done via methods and attributes of the Customer class)
    customerQueue.push(shopper);
}

unsigned long CashDesk::size() {
/// returns the amount of Customers standind in queue of that Cash Register
    return customerQueue.size();
}

Customer* CashDesk::pop() {
/// removes first Customer from the queue
    Customer* result = customerQueue.front();
    customerQueue.pop();
    return result;
}

Customer* CashDesk::scan(unsigned short scanSpeed) {
    itemsScaned += scanSpeed;
    if (customerQueue.front() -> getBasketSize() < itemsScaned) {
        itemsScaned = 0;
        return pop();
    }
    return nullptr;
}
