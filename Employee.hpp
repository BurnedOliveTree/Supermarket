#ifndef Employee_hpp
#define Employee_hpp

#include "Base.hpp"

class Employee {
/// Employee object, eaech representing a single employee
    std::string firstName;
    std::string lastName;
    std::string status;

public:
    Employee(std::string first, std::string last);
    std::string getName();
    // void employeet();
};

#endif /* Employee_hpp */
