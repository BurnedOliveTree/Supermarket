#include "CashDesk.hpp"

float checkCash(float cash);

CashDesk::CashDesk(amount argID, short x, short y, float cashIn) {
/// CashDesk object constructor
    objID = argID;
    std::pair<short, short> tempPair(x, y);
    position = tempPair;
    isOpen = false;
    cashAmount = checkCash(cashIn);
    assignee = nullptr;
}

amount CashDesk::getID() {
/// returns the ID of CashDesk object
    return objID;
}

bool CashDesk::operator ==(amount secondID) {
/// comparison operator overload comparing IDs of CashDesk object and a unsigned short
    if (getID() == secondID)
        return true;
    else
        return false;
}

bool CashDesk::operator !=(amount secondID) {
/// comparison operator overload comparing ID of CashDesk object and a unsigned short
    if (getID() != secondID)
        return true;
    else
        return false;
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
    if (getID() != cash2.getID())
        return true;
    else
        return false;
}

void CashDesk::open() {
/// sets this CashDesk status to open
    isOpen = true;
}

bool CashDesk::getState() {
/// return status of this CashDesk
    return isOpen;
}

void CashDesk::close() {
/// sets this CashDesk status to closed
    isOpen = false;
}

float CashDesk::getCash() {
    return cashAmount;
}

void CashDesk::addCash(float n) {
    n = checkCash(n);
    cashAmount += n;
}

void CashDesk::operator +=(float n) {
    addCash(n);
}

void CashDesk::setCash(float n) {
    n = checkCash(n);
    cashAmount = n;
}

void CashDesk::operator =(float n) {
    setCash(n);
}

void CashDesk::takeCash(float n) {
    n = checkCash(n);
    cashAmount -= n;
}

void CashDesk::operator -=(float n) {
    takeCash(n);
}

Employee* CashDesk::assign(Employee* assigned) {
/// assigns an Employee to the cash register and returns the previously assigned Employee, if there was any
    Employee* temp = assignee;
    assignee = assigned;
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
    for (int i=getQueueLength(); i>=0; --i) {
        if (customerQueue[i] == shopper)
            return i;
    }
    return -1;
}

int CashDesk::getQueueLength() {
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
