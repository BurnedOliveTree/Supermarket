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
    std::vector<Customer> customerContainer;
    std::vector<CashDesk> cashDeskContainer;
    std::vector<Product> productContainer;

public:
    amount getCustomerAmount();
    void createCustomer(amount argID);
    Customer& findCustomer(amount argID);
};

#endif /* Shop_hpp */
