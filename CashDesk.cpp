//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "CashDesk.hpp"

CashDesk::CashDesk(unsigned short argID, int cashIn) {
/// CashDesk object constructor
    objID = argID;
    isOpen = false;
    cashAmount = cashIn;
    assignee = nullptr;
}

unsigned short CashDesk::getID() {
/// returns the ID of CashDesk object
    return objID;
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

int CashDesk::getCash() {
    return cashAmount;
}

void CashDesk::addCash(int n) {
    cashAmount += n;
}

void CashDesk::operator +=(int n) {
    addCash(n);
}

void CashDesk::setCash(int n) {
    cashAmount = n;
}

void CashDesk::operator =(int n) {
    setCash(n);
}

void CashDesk::takeCash(int n) {
    cashAmount -= n;
}

void CashDesk::operator -=(int n) {
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

void CashDesk::standInLine(Customer* shopper) {
/// assigns a Customer to the CashDesk queue (checking whether Customer is already in a queue will be done via methods and attributes of the Customer class)
    customerQueue.push_back(shopper);
}

void CashDesk::operator +=(Customer* shopper) {
    standInLine(shopper);
}

int CashDesk::findInQueue(Customer* shopper) {
/// returns the position of a Customer in this Cash Register's queue
    for (unsigned long i = getQueueLength(); i >= 0; --i) {
        if (customerQueue[i] == shopper)
            return int(i);
    }
    return -1;
}

unsigned long CashDesk::getQueueLength() {
/// returns the amount of Customers standind in queue of that Cash Register
    return customerQueue.size();
}

void CashDesk::leaveTheQueue(Customer* shopper) {
/// removes given Customer from the queue
    int i = CashDesk::findInQueue(shopper);
    std::cout << i << " ";
    customerQueue.erase(customerQueue.begin()+i);
}

void CashDesk::operator -=(Customer* shopper) {
    leaveTheQueue(shopper);
}
