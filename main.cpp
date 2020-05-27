//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"
#include "Tests/TestInvoice.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void stupidTemporaryMethod() {
    unsigned long a;
    std::cout << "Podaj czas trwania [s]:" << std::endl;
    std::cin >> a;
    Shop simulation(a);
    simulation.run();
}

void manualTest() {
    std::cout << "Brak podanych argumentow." << std::endl << "Inicjacja manualnego dostepu do programu." << std::endl;
    TestInvoice invoiceTest;
    invoiceTest.menu();
}

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
            stupidTemporaryMethod();
//            manualTest();
            break;
        }
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
