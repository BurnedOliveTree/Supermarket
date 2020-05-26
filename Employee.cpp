//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Employee.hpp"

Employee::Employee(unsigned short argID, std::string first, std::string last) {
/// Employee object constructor, a primitive version of
    objID = argID;
    firstName = first;
    lastName = last;
    occupied = false;
}

unsigned short Employee::getID() {
/// returns the ID of Employee object
    return objID;
}

std::string Employee::getName() {
/// returns full name of this Employee
    return firstName+" "+lastName;
};

bool Employee::isOccupied() {
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
