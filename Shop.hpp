//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Shop_hpp
#define Shop_hpp

#include "Base.hpp"
#include "Product.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "CashDesk.hpp"

class Shop {
/// Shop object, representing the whole shop, containing all other objects (Employees, Customers, CashDesks etc.)
    std::vector<CashDesk> cashDeskContainer;
    std::vector<Customer> customerContainer;
    std::vector<Employee> employeeContainer;
    std::vector<Product> productContainer;
    unsigned long maxCustomerAmount;
    unsigned long maxCashDeskAmount;
    unsigned long maxEmployeeAmount;
    unsigned long maxProductAmount;

public:
    amount getCashDeskAmount();
    amount getCustomerAmount();
    void createCustomer();
    Customer& findCustomer(amount argID);
};

#endif /* Shop_hpp */
