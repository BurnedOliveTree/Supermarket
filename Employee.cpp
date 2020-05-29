//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Employee.hpp"

Employee::Employee(unsigned short argID, std::string argName) {
/// Employee object constructor, a primitive version of
    objID = argID;
    name = argName;
    occupied = false;
}

unsigned short Employee::getID() const {
/// returns the ID of Employee object
    return objID;
}

std::string Employee::getName() const {
/// returns full name of this Employee
    return name;
};

bool Employee::isOccupied() const {
/// returns current status of this Employee
    return occupied;
};

void Employee::setFree() {
/// changes current status of this Employee into free
    occupied = false;
};

void Employee::setBusy() {
/// changes current status of this Employee into busy
    occupied = true;
};
