//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef CashDesk_hpp
#define CashDesk_hpp

#include "Customer.hpp"
#include "Employee.hpp"

#include <iostream>
#include <vector>

class CashDesk {
/// CashDesk object, each representing a single cash register and it's queue of customers
    unsigned short objID;
    std::vector<Customer*> customerQueue;
    Employee* assignee;
    bool isOpen;
    float cashAmount;

public:
    CashDesk(unsigned short no, float cashIn);
    unsigned short getID();
    void open();
    bool getState();
    void close();
    float getCash();
    void addCash(float n);
    void setCash(float n);
    void takeCash(float n);
    Employee* assign(Employee* assigned);
    void standInLine(Customer* shopper);
    int findInQueue(Customer* shopper);
    unsigned long getQueueLength();
    void leaveTheQueue(Customer* shopper);
    
    bool operator ==(unsigned short secondID);
    bool operator ==(CashDesk cash2);
    bool operator !=(unsigned short secondID);
    bool operator !=(CashDesk cash2);
    void operator =(float n);
    void operator =(Employee* assigned);
    void operator +=(float n);
    void operator -=(float n);
    void operator +=(Customer* shopper);
    void operator -=(Customer* shopper);
    friend std::ostream& operator <<(std::ostream& output, CashDesk& cashDesk) {
        output << "Cash " << cashDesk.getID() << " is ";
        if (cashDesk.getState())
            output << "opened.";
        else
            output << "closed.";
        output << " It has " << cashDesk.getCash() << " cash in it and " << cashDesk.getQueueLength() << " people in the queue.";
        return output;
    };
};

#endif /* CashDesk_hpp */
