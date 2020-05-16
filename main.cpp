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
    switch(argc) {
        case 1:     break; // brak argumentow - prosba o wpisanie?
        case 2:     break; // nazwa pliku - odczyt z pliku
        default:    break; // moze po kolei: liczba cykli symulacji, ilosc klientow, ilosc pracownikow, ilosc kas
    }
    
    TestInvoice invoiceTest;
    invoiceTest.menu();
    return 0;
}
