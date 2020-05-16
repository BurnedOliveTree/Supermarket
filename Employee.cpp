//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Employee.hpp"

Employee::Employee(std::string first, std::string last) {
/// Employee object constructor, a primitive version of
    firstName = first;
    lastName = last;
}

std::string Employee::getName() {
/// returns full name of this Employee
    return firstName+" "+lastName;
};
