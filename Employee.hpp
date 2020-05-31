//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Employee_hpp
#define Employee_hpp

#include <string>

class EmployeeInterface {
public:
    virtual unsigned short getID() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isOccupied() const = 0;
    virtual void setFree() = 0;
    virtual void setBusy() = 0;
};

class Employee {
/// Employee object, eaech representing a single employee
    unsigned short objID;
    std::string name;
    bool occupied;

public:
    Employee(unsigned short argID, std::string argName);
    unsigned short getID() const;
    std::string getName() const;
    bool isOccupied() const;
    void setFree();
    void setBusy();
};

#endif /* Employee_hpp */
