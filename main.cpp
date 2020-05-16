//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Base.hpp"
#include "Product.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "CashDesk.hpp"
#include "Shop.hpp"
#include "Tests/TestInvoice.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "this function is yet to be handled" << std::endl;
    }
    TestInvoice invoiceTest;
    invoiceTest.menu();
    return 0;
}
