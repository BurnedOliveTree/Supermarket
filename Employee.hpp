//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Employee_hpp
#define Employee_hpp

#include <string>

class Employee {
/// Employee object, eaech representing a single employee
    unsigned short objID;
    std::string firstName;
    std::string lastName;
    bool occupied;

public:
    Employee(unsigned short argID, std::string first, std::string last);
    unsigned short getID() const;
    std::string getName() const;
    bool isOccupied() const;
    void setFree();
    void setBusy();
};

#endif /* Employee_hpp */
