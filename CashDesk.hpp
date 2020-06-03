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
#include <queue>

class CashDeskInterface {
public:
    virtual unsigned short getID() = 0;
    virtual void open(Employee* assigned) = 0;
    virtual bool getState() = 0;
    virtual Employee* close() = 0;
    virtual unsigned int getCash() = 0;
    virtual void addCash(unsigned int n) = 0;
    virtual void setCash(unsigned int n) = 0;
    virtual void takeCash(unsigned int n) = 0;
    virtual Employee* assign(Employee* assigned) = 0;
    virtual void push(Customer* shopper) = 0;
    virtual unsigned long size() = 0;
    virtual Customer* pop() = 0;
    virtual Customer* scan() = 0;
};

class CashDesk : public CashDeskInterface {
/// CashDesk object, each representing a single cash register and it's queue of customers
    unsigned short ID;
    std::queue<Customer*> customerQueue;
    Employee* assignee;
    bool isOpen;
    unsigned int cashAmount;
    unsigned short itemsScaned;

public:
    CashDesk(unsigned short no, unsigned int cashIn);
    unsigned short getID();
    void open(Employee* assigned);
    bool getState();
    Employee* close();
    unsigned int getCash();
    void addCash(unsigned int n);
    void setCash(unsigned int n);
    void takeCash(unsigned int n);
    Employee* assign(Employee* assigned);
    void push(Customer* shopper);
    unsigned long size();
    Customer* pop();
    Customer* scan();
    unsigned int checkout(Customer *customer);
    
    bool operator ==(unsigned short secondID);
    bool operator ==(CashDesk cash2);
    bool operator !=(unsigned short secondID);
    bool operator !=(CashDesk cash2);
    void operator =(unsigned int n);
    void operator +=(unsigned int n);
    void operator -=(unsigned int n);
    friend std::ostream& operator <<(std::ostream& output, CashDesk& cashDesk) {
        output << "Cash " << cashDesk.getID() << " is ";
        if (cashDesk.getState())
            output << "opened.";
        else
            output << "closed.";
        output << " It has " << cashDesk.getCash() << " cash in it and " << cashDesk.size() << " people in the queue.";
        return output;
    };
};

#endif /* CashDesk_hpp */
