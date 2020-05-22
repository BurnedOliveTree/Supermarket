//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Product.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "CashDesk.hpp"
#include "Shop.hpp"
#include "Tests/TestInvoice.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void manualTest();

/**
        Kolejnosc argumentow:
                czas, ilosc kas, ilosc pracownikow, ilosc klientow, ...
            lub
                nazwa pliku z wartosciami (w powyzszej kolejnosci).
        Brak argumentow skutkuje wlaczeniem recznego sterowania.
 */
int main(int argc, char* argv[]) {
    switch(argc) {
        case 0: case 1: {
            manualTest();
            break; }
        case 2: {
            Shop simulation(argv[1]);
            simulation.run();
            break;
        }
        default: {
            Shop simulation(argv);
            simulation.run();
        }
    }
    return 0;
}

void manualTest() {
    cout << "Brak podanych argumentow." << endl << "Inicjacja manualnego dostepu do programu." << endl;
    TestInvoice invoiceTest;
    invoiceTest.menu();
}
